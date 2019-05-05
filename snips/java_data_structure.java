import java.util.*;

public class Solution {
    public static void main(String[] args) {
        // collections in java / python is not as powerful as C++.
        // it's mainly because they donot have a powerful iterator.
        // maybe they are too weak for programming competition.

        // Array
        int[] intArray = new int[10];
        Arrays.fill(intArray, 0);
        intArray[1] = 1;
        Arrays.sort(intArray);
        Arrays.binarySearch(intArray, 0);
        int length = intArray.length;

        // TreeSet
        // Iterator for TreeSet in java is not as powerful as CPP
        // So you can only use a set 'as a set' and cannot use the tricks.
        TreeSet<Integer> treeSet = new TreeSet<>();
        treeSet.add(1);
        treeSet.add(2);
        treeSet.remove(1);
        treeSet.contains(2);
        // use IDE to check all its methods.
        
        // the headSet is backed by the origin set.
        treeSet.headSet(2);
        treeSet.tailSet(2);

        // map is just like set.
        TreeMap<Integer, Integer> treeMap = new TreeMap<>();

        Deque<Integer> deque = new ArrayDeque<>();
        PriorityQueue<Integer> priorityQueue = new PriorityQueue<>();

        ArrayList<Integer> arrayList = new ArrayList<>();
        LinkedList<Integer> linkedList = new LinkedList<>();
    }
}
