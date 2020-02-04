package model.ADT;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.atomic.AtomicInteger;

public class MyHeap<V> implements IMyHeap<V> {
    private Map<Integer, V> map;
    private AtomicInteger freeLocation;

    public MyHeap() {
        this.map = new ConcurrentHashMap<Integer, V>();
        this.freeLocation = new AtomicInteger(0);
    }

    @Override
    public int allocate(V value) {
        int newLocation = freeLocation.incrementAndGet();
        map.put(newLocation, value);
        return newLocation;
    }

    @Override
    public void update(int address, V value) {
        map.put(address, value);
    }

    @Override
    public V get(int address) {
        return map.get(address);
    }

    @Override
    public void deallocate(int address) {
        map.remove(address);
    }

    @Override
    public boolean isDefined(int address) {
        return map.containsKey(address);
    }

    @Override
    public Map<Integer, V> getContent() {
        return map;
    }

    @Override
    public void setContent(Map<Integer, V> content) {
        map = content;
    }

    @Override
    public String toString() {
        StringBuilder content = new StringBuilder();
        Iterator<HashMap.Entry<Integer, V>> it = map.entrySet().iterator();

        while (it.hasNext()) {
            HashMap.Entry<Integer, V> entry = it.next();
            content.append("(")
                    .append(entry.getKey())
                    .append("->")
                    .append(entry.getValue())
                    .append(")")
                    .append(", ");
        }
        return content.toString();
    }
}
