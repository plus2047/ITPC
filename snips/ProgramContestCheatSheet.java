package snips;

import java.util.*;

public class ProgramContestCheatSheet {
    public static void main(String[] args) {

        // Array
        // accroding to experiment
        // when dataset is large (may gc occurs) ArrayList<Integer> is much slower than primary array.
        // so always use primary array if possible.
        int[] intArray = new int[10];
        Arrays.fill(intArray, 0);
        intArray[1] = 1;
        Arrays.sort(intArray);
        Arrays.binarySearch(intArray, 0);
        System.out.printf("get array length: %s\n", intArray.length);
        System.out.println(String.format("default sorted primary array: %s", Arrays.toString(intArray)));

        // ArrayList
        ArrayList<Integer> array = new ArrayList<>();
        array.add(1);  // like push_back
        array.add(7);
        array.add(3);
        array.add(2);
        System.out.printf("get val by index: %s\n", array.get(0));
        array.sort(null);  // default sort
        System.out.println(String.format("default sorted arrayList: %s", array));
        array.sort((n1, n2) -> n2 - n1);
        System.out.println(String.format("inverse sorted arrayList: %s", array));

        // TreeSet
        TreeSet<Integer> treeSet = new TreeSet<>();
        for(int i = 3; i < 10; i++) {
            treeSet.add(i);
        }
        treeSet.remove(7);
        treeSet.contains(2);
        System.out.println(String.format("treeSet: %s", treeSet));        
        // those subset is backed by the origin set.
        System.out.println(String.format("headSet <5: %s", treeSet.headSet(5)));
        System.out.println(String.format("tailSet >=5: %s", treeSet.tailSet(5)));
        System.out.println(String.format("subSet [3, 6): %s", treeSet.subSet(3, 6)));
        System.out.println(String.format("first: %s", treeSet.first()));
        System.out.println(String.format("last: %s", treeSet.last()));

        // map is just like set.
        TreeMap<Integer, Integer> treeMap = new TreeMap<>();
        treeMap.put(1, 2);
        treeMap.remove(1);
        treeMap.get(1);  // return null if not exist

        // hashSet, hashMap. not support subset, etc
        // Set<Integer> set = new HashSet<>();
        // Map<Integer, Integer> map = new HashMap<>();

        // other containers
        Deque<Integer> deque = new ArrayDeque<>();
        deque.addFirst(0);
        deque.addLast(1);
        deque.peekFirst();
        deque.peekLast();
        deque.pollFirst();
        deque.pollLast();

        PriorityQueue<Integer> priorityQueue = new PriorityQueue<>();
        // PriorityQueue<Integer> reversedPriorityQueue = new PriorityQueue<>((n1, n2) -> n2 - n1);
        
        priorityQueue.add(1);
        priorityQueue.peek();
        priorityQueue.poll();

        // java iterator is strange.
        // it's better to image it point BETWEEN nodes.
        //    1   2   3   4   5   6
        //  ^
        // (pointer)
        // after call next (return 1):
        //    1   2   3   4   5   6
        //      ^
        LinkedList<Integer> linkedList = new LinkedList<>();
        linkedList.add(2);
        linkedList.addFirst(1);
        linkedList.addLast(3);
        linkedList.addLast(4);
        System.out.println(String.format("linkedList: %s", linkedList));
        ListIterator<Integer> iter = linkedList.listIterator();
        System.out.println(String.format("next: %s", iter.next()));
        System.out.println(String.format("next: %s", iter.next()));
        System.out.println(String.format("previous: %s", iter.previous()));
        iter.remove();  // remove the last returned element. be careful, it's 'direction' depends on the last call.
        System.out.println(String.format("linkedList after remove: %s", linkedList));
        iter.add(10);  // since iter points between two element, this method just insert here but before the iter.
        System.out.println(String.format("linkedList after add: %s", linkedList));
        iter.add(10);  // since iter points between two element, this method just insert here but before the iter.
        System.out.println(String.format("linkedList after add: %s", linkedList));
        System.out.println(String.format("next: %s", iter.next()));

        final int N = 10000000;
        int[] primaryArray = new int[N];
        Arrays.fill(primaryArray, 0);
        long begin;
        begin = System.nanoTime();
        int total = 0;
        for(int i = 1; i < N; i++) {
            primaryArray[i] = i * 2;
            total += primaryArray[i - 1];
        }
        System.out.printf("primary array time usage: %s ms, total: %s\n", (System.nanoTime() - begin) * 0.000001, total);

        ArrayList<Integer> arrayList = new ArrayList<>(N);
        begin = System.nanoTime();
        total = 0;
        arrayList.add(0);
        for(int i = 1; i < N; i++) {
            arrayList.add(i * 2);
            total += arrayList.get(i - 1);
        }
        System.out.printf("ArrayList time usage: %s ms, total:%s\n", (System.nanoTime() - begin) * 0.000001, total);
    }
}