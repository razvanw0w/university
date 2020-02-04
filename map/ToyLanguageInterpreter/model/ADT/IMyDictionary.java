package model.ADT;

import exceptions.MyException;

import java.util.Map;

public interface IMyDictionary<K, V> {
    public V lookup(K key);
    public void update(K key, V value);
    public boolean isDefined(K key);
    public void remove(K key) throws MyException;
    public Map<K, V> getContent();
    public void setContent(Map<K, V> content);
    public IMyDictionary<K, V> deepCopy();
}
