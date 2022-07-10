#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graph.h"

Graph *graph_create( int n, Graph_type t )
{
    int i;
    Graph *g = (Graph*)malloc(sizeof(*g));
    assert(g != NULL);
    assert(n > 0);

    g->n = n;
    g->m = 0;
    g->t = t;
    g->edges = (Edge**)malloc(n * sizeof(Edge*));
    assert(g->edges != NULL);
    g->in_deg = (int*)malloc(n * sizeof(*(g->in_deg)));
    assert(g->in_deg != NULL);
    g->out_deg = (int*)malloc(n * sizeof(*(g->out_deg)));
    assert(g->out_deg != NULL);
    for (i=0; i<n; i++) {
        g->edges[i] = NULL;
        g->in_deg[i] = g->out_deg[i] = 0;
    }
    return g;
}

void graph_destroy(Graph *g)
{
    int i;

    assert(g != NULL);

    for (i=0; i<g->n; i++) {
        Edge *edge = g->edges[i];
        while (edge != NULL) {
            Edge *next = edge->next;
            free(edge);
            edge = next;
        }
        g->edges[i] = NULL; /* e' superfluo */
    }
    free(g->edges);
    free(g->in_deg);
    free(g->out_deg);
    g->n = 0;
    g->edges = NULL;
    free(g);
}

Graph_type graph_type(const Graph *g)
{
    return g->t;
}

static Edge *new_edge(int src, int dst, double weight, Edge *next)
{
    Edge *edge = (Edge*)malloc(sizeof(Edge));
    assert(edge != NULL);

    edge->src = src;
    edge->dst = dst;
    edge->weight = weight;
    edge->next = next;
    return edge;
}

/* Inserisce l'arco (src, dst, weight) nel grafo; NON viene inserito
   l'arco opposto nel caso di grafo non orientato (occorre invocare
   due volte questa funzione). Questa funzione ritorna sempre 0; se si
   effettua il controllo sulla presenza di archi duplicati (controllo
   che aumenta il costo asintotico di questa operazione), la funzione
   restituisce true (nonzero) se e solo se l'arco (src, dst) esiste
   già e quindi non viene inserito. */
static int graph_adj_insert(Graph *g, int src, int dst, double weight)
{
#if 0
    const Edge *e;

    /* Se si vuole rendere l'operazione più robusta, controlliamo che
       l'arco non esista già. */
    e = graph_adj(g, src);
    while ((e != NULL) && (e->dst != dst)) {
        e = e->next;
    }
    /* Arrivati qui abbiamo che e == NULL se e solo se l'arco
       non è stato trovato. */
    if (e != NULL) {
        return 1;
    }
#endif
    /* Inseriamo l'arco all'inizio della lista di adiacenza.  Se non
       ci fosse il controllo precedente, l'inserimento di un arco
       richiederebbe tempo O(1) */
    g->edges[src] = new_edge(src, dst, weight, g->edges[src]);
    g->in_deg[dst]++;
    g->out_deg[src]++;
    return 0;
}

void graph_add_edge(Graph *g, int src, int dst, double weight)
{
    int status = 0;

    assert(g != NULL);

    assert((src >= 0) && (src < graph_n_nodes(g)));
    assert((dst >= 0) && (dst < graph_n_nodes(g)));

    status = graph_adj_insert(g, src, dst, weight);
    if (graph_type(g) == GRAPH_UNDIRECTED) {
        status |= graph_adj_insert(g, dst, src, weight);
    }
    if (status == 0)
        g->m++;
    else
        fprintf(stderr, "Ho ignorato l'arco duplicato (%d,%d)\n", src, dst);
}

int graph_n_nodes(const Graph *g)
{
    assert(g != NULL);

    return g->n;
}

int graph_n_edges(const Graph *g)
{
    assert(g != NULL);

    return g->m;
}

int graph_out_degree(const Graph *g, int v)
{
    assert(g != NULL);
    assert((v >= 0) && (v < graph_n_nodes(g)));
    return g->out_deg[v];
}

int graph_in_degree(const Graph *g, int v)
{
    assert(g != NULL);
    assert((v >= 0) && (v < graph_n_nodes(g)));
    return g->in_deg[v];
}

Edge *graph_adj(const Graph *g, int v)
{
    assert(g != NULL);
    assert((v >= 0) && (v < graph_n_nodes(g)));

    return g->edges[v];
}

void graph_print(const Graph *g)
{
    int i;

    assert(g != NULL);

    if (graph_type(g) == GRAPH_UNDIRECTED) {
        printf("UNDIRECTED\n");
    } else {
        printf("DIRECTED\n");
    }

    for (i=0; i<g->n; i++) {
        const Edge *e;
        int out_deg = 0; /* ne approfittiamo per controllare la
                            correttezza dei gradi uscenti */
        printf("[%2d] -> ", i);
        for (e = graph_adj(g, i); e != NULL; e = e->next) {
            printf("(%d, %d, %f) -> ", e->src, e->dst, e->weight);
            out_deg++;
        }
        assert(out_deg == graph_out_degree(g, i));
        printf("NULL\n");
    }
}

Graph *graph_read_from_file(FILE *f)
{
    int n, m, t;
    int src, dst;
    int i; /* numero archi letti dal file */
    double weight;
    Graph *g;

    assert(f != NULL);

    if (3 != fscanf(f, "%d %d %d", &n, &m, &t)) {
        fprintf(stderr, "ERRORE durante la lettura dell'intestazione del grafo\n");
        abort();
    };
    assert( n > 0 );
    assert( m >= 0 );
    assert( (t == GRAPH_UNDIRECTED) || (t == GRAPH_DIRECTED) );

    g = graph_create(n, t);
    /* Ciclo di lettura degli archi. Per rendere il programma più
       robusto, meglio non fidarsi del valore `m` nell'intestazione
       dell'input. Leggiamo informazioni sugli archi fino a quando ne
       troviamo, e poi controlliamo che il numero di archi letti (i)
       sia uguale a quello dichiarato (m) */
    i = 0;
    while (3 == fscanf(f, "%d %d %lf", &src, &dst, &weight)) {
        graph_add_edge(g, src, dst, weight);
        i++;
    }
    if (i != m) {
        fprintf(stderr, "WARNING: ho letto %d archi, ma l'intestazione ne dichiara %d\n", i, m);
    }
    /*
    fprintf(stderr, "INFO: Letto grafo %s con %d nodi e %d archi\n",
            (t == GRAPH_UNDIRECTED) ? "non orientato" : "orientato",
            n,
            m);
    */
    return g;
}

void graph_write_to_file( FILE *f, const Graph* g )
{
    int v;
    int n, m, t;

    assert(g != NULL);
    assert(f != NULL);

    n = graph_n_nodes(g);
    m = graph_n_edges(g);
    t = graph_type(g);

    fprintf(f, "%d %d %d\n", n, m, t);
    for (v=0; v<n; v++) {
        const Edge *e;
        for (e = graph_adj(g, v); e != NULL; e = e->next) {
            assert(e->src == v);
            /* Se il grafo è non orientato, dobbiamo ricordarci che
               gli archi compaiono due volte nelle liste di
               adiacenza. Nel file pero' dobbiamo riportare ogni arco
               una sola volta, dato che sarà la procedura di lettura a
               creare le liste di adiacenza in modo corretto. Quindi,
               ogni coppia di archi (u,v), (v,u) deve comparire una
               sola volta nel file. Per comodità, salviamo nel file la
               versione di ciascun arco in cui il nodo sorgente è
               minore del nodo destinazione. */
            if ((graph_type(g) == GRAPH_DIRECTED) || (e->src < e->dst)) {
                fprintf(f, "%d %d %f\n", e->src, e->dst, e->weight);
            }
        }
    }
}
