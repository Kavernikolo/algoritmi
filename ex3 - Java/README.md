## Esercizio 3

### Linguaggio richiesto: Java

### Testo

Si implementi una libreria che realizza la struttura dati Heap Minimo. La struttura dati deve:
- rappresentare internamente lo heap tramite un vettore (è possibile usare anche altre strutture interne di supporto, se necessarie);
- consentire un numero qualunque e non noto a priori di elementi dello heap;
- essere generica per quanto riguarda il tipo degli elementi dello heap;
- essere generica per quanto riguarda il criterio di confronto fra elementi dello heap.

Essa deve, inoltre, offrire (almeno) le seguenti operazioni (accanto a ogni operazione è specificata la
complessità richiesta, in cui n indica il numero di elementi dello heap):
- creazione di uno heap minimo vuoto - O(1);
- inserimento di un elemento - O(log n);
- restituzione della dimensione dello heap - O(1);
- restituzione del genitore di un elemento - O(1);
- restituzione del figlio sinistro di un elemento - O(1);
- restituzione del figlio destro di un elemento - O(1);
- estrazione dell'elemento con valore minimo - O(log n);
- diminuzione del valore di un elemento - O(log n).

Una descrizione della struttura dati Heap è riportata sui lucidi e le dispense fornite nella parte di teoria del corso,
 nonché sul testo Cormen et al, `Introduzione agli algoritmi e strutture dati`, McGraw-Hill, Terza edizione, 2010, nel capitolo `Heapsort`. In particolare, si suggerisce il riferimento al testo per tutti quegli aspetti non esplicitamente trattati a lezione.

### Unit Testing

Implementare gli unit-test per la libreria secondo le indicazioni suggerite nel documento Unit Testing.