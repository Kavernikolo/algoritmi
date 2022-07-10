import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import org.junit.Before;
import org.junit.Test;

public class GraphTests
{
  private Graph<Integer, Double> directGraph;
  private Graph<Integer, Double> undirectGraph;

  private Integer v1, v2, v3, v4, v5, v6, v7;
  private Double num1, num2, num3, num4, num5;

  @Before
  public void createGraph() throws GraphException 
  {
    
    directGraph = new Graph < Integer, Double > (true);
    undirectGraph = new Graph < Integer, Double > (false);

    v1 = 1;
    v2 = 2;
    v3 = 3;
    v4 = 4;
    v5 = 5;
    v6 = 6;
    v7 = 7;
    num1 = 10.0;
    num2 = 5.0;
    num3 = 9.0;
    num4 = 2.0;
    num5 = 4.0;

    directGraph.addNode(v1);
    directGraph.addNode(v2);
    directGraph.addNode(v3);
    directGraph.addNode(v4);
    directGraph.addNode(v5);
    directGraph.addNode(v6);
    directGraph.addNode(v7);

    directGraph.addEdge(v1, v2, num1);
    directGraph.addEdge(v2, v3, num2);
    directGraph.addEdge(v1, v3, num3);
    directGraph.addEdge(v4, v6, num4);
    directGraph.addEdge(v7, v2, num5);
    directGraph.removeEdge(v6, v7);
    directGraph.removeNode(v6);
  }

  @Test
  public void existVertex1() throws Exception {
    assertTrue(directGraph.hasNode(v1));
  }

  @Test
  public void existVertex2() throws Exception {
    assertTrue(directGraph.hasNode(v2));
  }

  @Test
  public void existVertex3() throws Exception {
    assertTrue(directGraph.hasNode(v3));
  }

  @Test
  public void existEdge() throws Exception {
    assertTrue(directGraph.hasEdge(v1, v2));
  }

  @Test
  public void numberVertex() throws Exception {
    assertEquals(directGraph.countNode(), 6);
  }

  @Test
  public void numberEdge() throws Exception {
    assertEquals(directGraph.countEdge(), 5);
  }

  @Test
  public void GraphUnDirected() throws Exception {
    Graph < Integer, Double > directGraph2;
    directGraph2 = new Graph < Integer, Double > (true);
    assertTrue(directGraph2.isDirect());
  }

  @Test
  public void GraphDirected() throws Exception {
    assertFalse(undirectGraph.isDirect());
  }

  @Test
  public void WeigthEdge() throws Exception {
    assertTrue(directGraph.getLabel(v7, v2) == 4.0);
  }
}
