package model.ADT;

import exceptions.MyException;

import java.util.Iterator;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.stream.Collectors;

public class MyDictionary<K, V> implements IMyDictionary<K, V> {
    private Map<K, V> map;

    public MyDictionary() {
        map = new ConcurrentHashMap<K, V>();
    }

    @Override
    public V lookup(K key) {
        return map.get(key);
    }

    @Override
    public void update(K key, V value) {
        map.put(key, value);
    }

    @Override
    public boolean isDefined(K key) {
        return map.containsKey(key);
    }

    @Override
    public void remove(K key) throws MyException {
        if (!map.containsKey(key)) {
            throw new MyException("key isn't in the map for removal");
        }
        map.remove(key);
    }

    @Override
    public Map<K, V> getContent() {
        return map;
    }

    @Override
    public void setContent(Map<K, V> content) {
        map = content;
    }

    @Override
    public IMyDictionary<K, V> deepCopy() {
        HashMap<K, V> newMap = new HashMap<K, V>(map);
        MyDictionary<K, V> newDictionary = new MyDictionary<K, V>();
        newDictionary.setContent(newMap);
        return newDictionary;
    }

    @Override
    public String toString() {
        StringBuilder content = new StringBuilder();
        Iterator<HashMap.Entry<K, V>> it = map.entrySet().iterator();

        while (it.hasNext()) {
            HashMap.Entry<K, V> entry = it.next();
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
