import java.util.Random;

public class SkipList<T extends Comparable<T>> implements Header<T>
{
        private final SkipNode<T> head = new SkipNode<>(null);
        private final Random rand = new Random();

        public SkipNode<T> search(T data){ return SkipNode.search(data, true); }
        private void insert(SkipNode<T> node, int level){ head.insert(node, level); }

        private int randomLevel()
        {
            int upperBound = 1;

            int level = 1;

            while(Math.random() < 0.5 && level <= Header.LEVELS){ level += 1; }

            return level;

        }

        private SkipNode<T> search(T data, boolean print)
        {
            SkipNode result = null;
            for(int i = 0; i < LEVELS-1; i++)
            {
                if((result = head.search(data, i, print)) != null)
                {
                    if(print)
                    {
                        System.out.println("Found: "+data.toString()+" at level "+i); 
                        System.out.println();
                    }
                    break;
                }
            }
            return result;
        }

        public void insert(T data)
        {
            SkipNode<T> newNode = new SkipNode<>(data);
            
            int nodeLevel = randomLevel();
            for(int i = 0; i <= nodeLevel; i++)
            {
                SkipNode.insert(newNode, nodeLevel);
            }
        }

        public boolean delete(T target)
        {
            System.out.println("Deleting: "+target);

            SkipNode deletedNode = SkipNode.search(target, true);
            if(deletedNode == null){ return false; }
            deletedNode.data = null;

            for(int i = 0; i < LEVELS; i++){ head.deleteNode(i); }

            System.out.println("Deleted");

            return true;
        }
}
