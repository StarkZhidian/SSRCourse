本文标题大纲：

@[toc]
## 前言

在上篇文章中，我们将剩下的常见的 `Map` 接口下的相关具体类做了一个解析，还有一些相关的类将会在下一篇文章中做一个总结，这篇我们来看看 `Set` 接口的相关类。老规矩，还是继续看一下 `Set` 接口下继承关系图：

![](https://img-blog.csdn.net/20180606093406336?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0hhY2tlcl9aaGlEaWFu/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

和 `List`、`Map` 接口很类似：`Set` 接口提供了两个子类和接口 `AbstractSet` 类和 `SortedSet`接口，类比之前介绍 `Map` 接口下的 `AbstractMap` 类和 `SortedMap` 接口，我们就可以知道：`AbstractSet` 类最大化的实现了 `Set` 接口中的一些抽象方法，使得其子类可以以最小的代价来实现一个 `Set` 具体类。而 `SortedSet` 则是提供了一个将元素按照某种规则排序的一种约定。在 `SortedSet` 中提供了一个方法：

```java
/**
  * Returns the comparator used to order the elements in this set,
  * or <tt>null</tt> if this set uses the {@linkplain Comparable
  * natural ordering} of its elements.
  *
  * @return the comparator used to order the elements in this set,
  *         or <tt>null</tt> if this set uses the natural ordering
  *         of its elements
  */
Comparator<? super E> comparator();
```

很明显这是一个用于得到元素之间的比较器（Comparator）对象的一个方法，我们来看看其返回的 `Comparator` 接口：

```java
public interface Comparator<T> {
	// ...
    /**
     * 用于比较两个元素大小的方法，如果返回正数，证明 o1 > o2，如果返回负数，
     * 则 o1 < o2，如果返回 0，证明 o1 == o2
     */
    int compare(T o1, T o2);
    // ...
}
```

这个接口关键的方法就是 `compare` 方法，其实在 `TreeMap` 中也用到了，因为 `TreeMap` 会将键值对元素按键的顺序排序，那么具体的排序规则就看你如何重写这个方法了。下面来看一下 `Set` 接口下一些具体的类：

## HashSet

**这个类用来尽量保证以 O(1) 的时间复杂度来添加/判断元素存在/移除元素等**。在之前我们已经知道了 `HashMap` 的原理，而记得在第一篇介绍 `Map` 的文章中就已经说过为什么先介绍 `Map` 再介绍 `Set` ，我们直接来看看 `HashSet` 的源码吧，看完之后可能你就会觉得确实是这样的：

```java
public class HashSet<E>
    extends AbstractSet<E>
    implements Set<E>, Cloneable, java.io.Serializable
{
    private transient HashMap<E,Object> map;

    // Dummy value to associate with an Object in the backing Map
    private static final Object PRESENT = new Object();

    public HashSet() {
        map = new HashMap<>();
    }

    public HashSet(int initialCapacity, float loadFactor) {
        map = new HashMap<>(initialCapacity, loadFactor);
    }

    public HashSet(int initialCapacity) {
        map = new HashMap<>(initialCapacity);
    }
	// !!! 注意这个方法，是个彩蛋
    HashSet(int initialCapacity, float loadFactor, boolean dummy) {
        map = new LinkedHashMap<>(initialCapacity, loadFactor);
    }

    /**
     * 返回当前集合迭代器（Iterator）对象，用于遍历集合中的元素
     */
    public Iterator<E> iterator() {
        return map.keySet().iterator();
    }

    /**
     * 返回当前集合中元素的个数
     */
    public int size() {
        return map.size();
    }

    /**
     * 判断当前集合是否为空集合
     */
    public boolean isEmpty() {
        return map.isEmpty();
    }

    /**
     * 判断对象 o 是否存在当前集合中（通过 equals 方法判断等价）
     */
    public boolean contains(Object o) {
        return map.containsKey(o);
    }

    /**
     * 向当前集合元素中添加一个元素 e
     */
    public boolean add(E e) {
        return map.put(e, PRESENT)==null;
    }

    /**
     * 移除参数所代表的元素（通过 equals 方法比较等价），移除成功返回 true，否则返回 false
     */
    public boolean remove(Object o) {
        return map.remove(o)==PRESENT;
    }

    /**
     * 清除当前 Set 集合中所有的元素
     */
    public void clear() {
        map.clear();
    }
    // ... 
```

大部分的常用方法就是这些（添加元素、移除元素、遍历...），我们可以看到，所有对元素的相关操作都交给了其内部的一个 `HashMap` 对象处理，而添加进 `HashSet` 中的元素其实都是作为“键”储存在了这个 `HashMap` 对象中，那么其对应的值呢？当然是那个 `Object` 类型的  `PRESENT` 对象啦。同时在返回遍历元素的迭代器的时候，也是返回了 `HashMap` 对象中对应的 `keySet` 的迭代器。这么一来，你只要知道了 `HashMap` 的运行机制，`HashSet` 对你来说就没有任何问题了。关于 `HashMap` 的运行机制，可以参考之前的文章：[Java 集合框架（5）---- Map 相关类解析（中）](https://blog.csdn.net/Hacker_ZhiDian/article/details/81711358#hashmap)

## TreeSet

**这个类可以使得添加进入 `Set` 集合中的元素按照某种规则来排序**，但是其并不是直接实现 `SortedSet` 接口，而是实现了 `SortedSet` 的一个子接口 `NavigableSet`，其实 `TreeMap` 本身也没有直接实现 `SortedMap` 接口，而是实现了其的一个子接口 `NavigableMap` 。而和 `HashSet` 类似，其内部也是借助了一个 `TreeMap` 类型的对象来实现相关的操作。关于 `TreeMap` 可以参考：[Java 集合框架（5）---- Map 相关类解析（中）](https://blog.csdn.net/Hacker_ZhiDian/article/details/81711358#treemap) 。

#### NavigableSet

先来看看 `NavigableSet` 的源码：

```java
public interface NavigableSet<E> extends SortedSet<E> {
    // 返回当前集合中小于 e 的最大的元素
    E lower(E e);

    // 返回当前集合中不大于 e 的最大的元素
    E floor(E e);

    // 返回当前集合中不小于 e 的最小的元素
    E ceiling(E e);

    // 返回当前集合中大于 e 的最小的元素
    E higher(E e);

    // 返回并移除当前集合中的第一个（最小的）元素
    E pollFirst();

    // 返回并移除当前集合中的最后一个（最大的）元素
    E pollLast();

    // 按元素升序顺序返回遍历元素的迭代器
    Iterator<E> iterator();

    // 按元素降序顺序返回遍历另一个包含元素的集合
    NavigableSet<E> descendingSet();

    // 按元素降序顺序返回遍历元素的迭代器，和上面的 iterator 方法相反
    Iterator<E> descendingIterator();

    // 返回一个子集合，大于 fromElement 并小于 toElement，
    // 是否包含 fromElement 和 toElement 取决于 fromInclusive 和 toInclusive 参数是否为 true
    NavigableSet<E> subSet(E fromElement, boolean fromInclusive,
                           E toElement,   boolean toInclusive);
	// ...
}

```

可以看到 `NavigableSet` 接口声明了一些返回集合中一些特定元素/子集合的方法，下面来看看 `TreeSet` 的源码：

```java
public class TreeSet<E> extends AbstractSet<E>
    implements NavigableSet<E>, Cloneable, java.io.Serializable
{
    /**
     * The backing map. 用到的 TreeMap 对象
     */
    private transient NavigableMap<E,Object> m;

    // Dummy value to associate with an Object in the backing Map
    // 固定的值对象
    private static final Object PRESENT = new Object();

    TreeSet(NavigableMap<E,Object> m) {
        this.m = m;
    }

    public TreeSet() {
        this(new TreeMap<E,Object>());
    }
	/**
     * 构造方法，传入用于比较元素大小的 Comparator 类型的比较器。
	 * 如果元素类型实现了 Comparable 接口，那么不穿这个参数也是可以的，
	 * TreeMap 会使用元素实现的 Comparable 接口中的 compareTo 来比较两个元素的大小
	 */
    public TreeSet(Comparator<? super E> comparator) {
        this(new TreeMap<>(comparator));
    }

    public TreeSet(SortedSet<E> s) {
        this(s.comparator());
        addAll(s);
    }

    /**
     * 返回升序（相对 Comparator 的 compare 方法而言）遍历元素的迭代器
     */
    public Iterator<E> iterator() {
        return m.navigableKeySet().iterator();
    }

    /**
     *  返回逆序遍历元素的迭代器，和上一个方法相反
     */
    public Iterator<E> descendingIterator() {
        return m.descendingKeySet().iterator();
    }
    
    public int size() {
        return m.size();
    }

    public boolean isEmpty() {
        return m.isEmpty();
    }

    public boolean contains(Object o) {
        return m.containsKey(o);
    }

    public boolean add(E e) {
        return m.put(e, PRESENT)==null;
    }

    public boolean remove(Object o) {
        return m.remove(o)==PRESENT;
    }

    public void clear() {
        m.clear();
    }
    
    // ...
    
    public E first() {
        return m.firstKey();
    }

    public E last() {
        return m.lastKey();
    }

    public E lower(E e) {
        return m.lowerKey(e);
    }

    public E floor(E e) {
        return m.floorKey(e);
    }
    
    // ...
}
```

同样的，也是内部借助了一个 `TreeMap` 对象来实现的相关方法。所以只要你理解 `TreeMap` 的运行原理，那么 `TreeSet` 对你来说也没有任何问题。下面来看一下最后一个 `Set` 的具体类：`LinkedHashSet`:

## LinkedHashSet

就像 `HashMap` 和 `LinkedHashMap` 的关系一样，`LinkedHashSet` 是继承了 `HashSet` 的，这个类的作用时**保证遍历元素得到的元素序列的顺序和插入元素的先后顺序一样**。而其中没有重写任何操作元素的方法，我们来看看：

```java
public class LinkedHashSet<E>
    extends HashSet<E>
    implements Set<E>, Cloneable, java.io.Serializable {

    public LinkedHashSet(int initialCapacity, float loadFactor) {
        super(initialCapacity, loadFactor, true);
    }

    public LinkedHashSet(int initialCapacity) {
        super(initialCapacity, .75f, true);
    }

    public LinkedHashSet() {
        super(16, .75f, true);
    }

    public LinkedHashSet(Collection<? extends E> c) {
        super(Math.max(2*c.size(), 11), .75f, true);
        addAll(c);
    }
    // ...
}
```

第一眼看到这个类，我也有点吃惊： what！！？就提供了构造方法？没有重写任何一个操作元素的方法？那怎么来维持元素的相对顺序？（疑问三连）。但是我们注意到提供的三个构造方法都是调用了父类中具有 3 个参数的构造方法，那么我们赶紧去其父类（`HashSet`）中看看这个构造方法：

```java
HashSet(int initialCapacity, float loadFactor, boolean dummy) {
    map = new LinkedHashMap<>(initialCapacity, loadFactor);
}
```

看到这里我终于松了口气，这里的构造方法创建的是 `LinkedHashMap` 对象，我们通过前面的篇幅已经知道 **`LinkedHashMap` 是可以保证元素的遍历顺序是和元素插入顺序一样的**，因为它就是做这个工作的。关于其运行元素可以参考 [Java 集合框架（6）---- Map 相关类解析（下）](https://blog.csdn.net/Hacker_ZhiDian/article/details/84205845#LinkedHashMap_10) 。我们继续，既然这里创建的是 `LinkedHashMap` 对象，而同时 `HashSet` 将所有操作元素的相关方法都交给了对应的 map 来做，那么在这里我们调用 `LinkedHashSet` 中的一些操作元素的方法其实都是调用的 `LinkedHashMap` 中的相关方法，那么自然可以保证元素的遍历顺序和插入顺序一致。

好了，对 `Set` 接口的接口就到这里了，因为这里用到的都是 `Map` 接口下的相关具体类，所以篇幅并不是很长，关键还是对相关 `Map` 接口下的相关具体类的理解。在下一篇文章中我们将一起对整个 Java 集合框架做一个总结，也算是深入 Java 集合框架的系列的一个结束篇吧。

如果文章中有什么不正确的地方，还请多多指点，如果觉得我写的对您有帮助，请不要吝啬您的赞。

谢谢观看。。。