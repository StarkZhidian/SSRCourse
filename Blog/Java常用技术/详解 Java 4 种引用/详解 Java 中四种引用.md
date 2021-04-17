[TOC]

## 前言

在 Java 中，引用随处可见，我们通过类似 `Object obj = new Object();` 的代码就可以创建一个引用，而我们直接通过这个代码段创建的引用被称为强引用（`StrongReference`），这种引用的特点是其指向的对象无论如何都不会被 JVM 的垃圾回收器（`Garbage Collector`）回收（即使是面临着发生 `OutOfMemoryError` 异常的风险）。

但是可能在开发中，我们可能会需要一些具有其他特性的引用对象，比如说：我们需要某种引用可以提供这种功能：在新建其他对象时，如果当前堆内存足够用来分配给要新建的对象时，那么垃圾回收器不会回收这种引用指向的对象，但是如果当前可分配的堆内存不足时，我们希望垃圾回收器可以回收这种引用指向的对象，以提供足够的内存来创建新的对象。

## 另外三种引用

而在 JDK 1.2 之后，Java 提供了除了强引用之外的另外三种引用，他们分别是：`软引用（SoftReference）、弱引用（WeakReference）、虚引用（PhantomReference）`。通过他们我们可以实现我们上面所说的应用场景。下面一起来看一下这 3 中引用。

#### 软引用

这种引用的功能即是前言部分提到的：如果某个 Java 对象只被软引用所指向，那么在 JVM 要新建一个对象的时候，如果当前虚拟机所剩下的堆内存不足以保存这个要新建的对象的时候（即虚拟机将要抛出 `OutOfMemoryError` 异常的时候），那么 JVM 会发起一次垃圾回收（gc）动作，将堆中所 **只被非强引用** 指向的对象回收，以提供更多的可用内存来新建这个对象，如果经过垃圾回收动作之后虚拟机的堆内存中仍然没有足够的可用空间来创建这个对象，那么虚拟机将抛出一个 `OutOfMemoryError` 异常。在 Java 1.2 之后，提供了 `SoftReference` 类来表示软引用。

#### 弱引用

和软引用类似，但是弱引用的引用强度更弱一点，上文说到：只被软引用指向的对象会在 JVM 在新建对象并且其可用的堆内存不足以保存这个对象时会被垃圾回收器回收。即当 JVM 在新建一个对象并且第一次面临着抛出 `OutOfMemoryError` 异常时会被垃圾回收器回收。

而对于只被弱引用指向的对象来说，其只能存活到下一次 JVM 执行垃圾回收动作之前。也就是说：JVM 的每一次垃圾回收动作都会回收那些只被弱引用指向的对象。在 Java 1.2 之后，提供了 `WeakReference` 类来表示弱引用。

#### 虚引用

引用强度最弱的引用，这种引用有点特殊：被虚引用完全不会引用其所指向的对象的生命周期，也就是说一个 Java 对象是否被回收和指向它的虚引用完全没有任何关系。也不能通过虚引用来得到其指向的对象（其 `get` 方法直接返回 null）。那么虚引用有什么作用呢？虚引用一般会配合 `引用队列（ReferenceQueue）`来使用。当某个被虚引用指向的对象被回收时，我们可以在其引用队列中得到这个虚引用的对象作为其所指向的对象被回收的一个通知。我们将会在后面看到这种用法。

## 实验代码

好了，理论说完了，下面我们来实践一下：我们新建一个 Java 工程，在里面新建一个类 `Main` 并添加实践代码（请谨慎尝试）：

```java
public class Main {

	// 引用测试类
	static class ReferenceTest {

		static final int _1M = 1024;
         // 引用队列，当某个引用所指向的对象被回收时这个引用本身会被添加到其对应的引用队列中
         // 其泛型为其中存放的引用要指向的对象类型
		ReferenceQueue<Object> referenceQueue = new ReferenceQueue<>();

		// 强引用测试
		void testStrongReference() {
			ArrayList<byte[]> strongReferences = new ArrayList<>();
			try {
				while (true) {
					strongReferences.add(new byte[_1M]);
				}
			} catch (OutOfMemoryError e) {
				e.printStackTrace();
			}
		}

		// 软引用测试
		void testSoftReference() {
			ArrayList<SoftReference> softReferences = new ArrayList<>();
			try {
				while (true) {
					softReferences.add(new SoftReference<>(new byte[_1M], referenceQueue));
				}
			} catch (OutOfMemoryError e) {
				e.printStackTrace();
			}
		}

		// 弱引用测试
		void testWeakReference() {
			ArrayList<WeakReference> weakReferences = new ArrayList<>();
			try {
				while (true) {
					weakReferences.add(new WeakReference<>(new byte[_1M], referenceQueue));
				}
			} catch (OutOfMemoryError e) {
				e.printStackTrace();
			}
		}

		// 虚引用测试
		void testPhantomReference() {
			ArrayList<PhantomReference<byte[]>> phantomReferences = new ArrayList<>();
			try {
				while (true) {
					phantomReferences.add(new PhantomReference<>(new byte[_1M], referenceQueue));
				}
			} catch (OutOfMemoryError e) {
				e.printStackTrace();
			}
		}
	}

	public static void main(String[] args) {
		ReferenceTest test = new ReferenceTest();
		test.testStrongReference();
	}
}
```

我们在 `Main` 类中创建了一个静态内部类 `ReferenceTest`，并在其中提供了 4 个方法，方法很简单，就是不断创建新的 `byte` 数组，并且用不同类型的引用对象指向它。直到发生 `OutOfMemoryError` 异常。先来看看强引用的测试结果：

![](C:\Users\MAIBENBEN\Desktop\blog\详解 Java 4 种引用\1.png)

运行过程中你会看到电脑内存占用飙升，最后会抛出 `OutOfMemoryError` 异常，这个结果是显而易见的，现在来看看对软引用的测试，修改一下 `main` 方法中的代码：`test.testSoftReference();`

![](C:\Users\MAIBENBEN\Desktop\blog\详解 Java 4 种引用\2.png)

同样的你会看到电脑占用内存飙升，但是最终会稳定一个值：因为我们现在用的是软引用来指向一个个 `byte` 数组。在 JVM 抛出 `OutOfMemoryError` 异常之前会将只被软引用指向的对象回收掉（通过执行垃圾回收动作），因此不会抛出 `OutOfMemoryError` 异常。下面来看看对弱引用的测试，我们改一下 `main` 方法中的一行代码：`test.testWeakReference();`

![](C:\Users\MAIBENBEN\Desktop\blog\详解 Java 4 种引用\2.png)

同样的你会看到相同的结果，原因也正如上文所说：JVM 的垃圾回收动作会回收掉所有只被弱引用指向的对象。最后来看看虚引用的测试，同样的修改 `main` 方法中的一行代码：`test.testPhantomReference();`

![](C:\Users\MAIBENBEN\Desktop\blog\详解 Java 4 种引用\3.png)

你会看到和强引用测试一样的结果：JVM 最终会抛出一个 `OutOfMemoryError` 异常。可能有些小伙伴们会问了：虚引用不是引用强度最弱的的吗，怎么会因为它而抛出 `OutOfMemoryError` 异常呢？其实仔细一想：虚引用确实是引用强度最弱的，但是还有一点是虚引用根本不会影响对象的声明周期，也就是说某个对象是否被 JVM 的垃圾回收动作回收和这个对象是否被虚引用所指向和被多少个虚引用所指向没有任何关系，既然其不会影响对象的生命周期，那么使用和不使用虚引用指向对象对这个对象是否被 JVM 回收是没有任何区别的，那么我们就可以将其看做没有使用虚引用时的代码，此时效果自然和直接使用强引用一样。关于这个，可以参考 `PhantomReference` 类的源码注释：

	>Unlike soft and weak references, phantom references are not automatically cleared by the garbage collector as they are enqueued.  An object that is reachable via phantom references will remain so until all such references are cleared or themselves become unreachable.

## 引用队列

在上节的代码中，我们新建了一个引用队列（ReferenceQueue）对象，并且在创建软引用、弱引用和虚引用对象时将其作为参数传入对应引用的构造方法中。在文章的开头提到过可以利用引用队列来检测某个引用指向的对象是否被垃圾回收器回收，那么具体应该怎么做呢。我们可以看一下 3 类引用的源码，这里以弱引用为例（剩余两种可以类比）：

```java
public class WeakReference<T> extends Reference<T> {
    
    public WeakReference(T referent) {
        super(referent);
    }

    public WeakReference(T referent, ReferenceQueue<? super T> q) {
        super(referent, q);
    }
}
```

可以看到 `WeakReference` 类继承了 `Reference` 类，可以猜到 `Reference` 类是 3 种引用的基类，我们看看这个类的源码 `Reference.java`：

```java
public abstract class Reference<T> {

    private T referent;         /* Treated specially by GC */

    volatile ReferenceQueue<? super T> queue;

    /* When active:   NULL
     *     pending:   this
     *    Enqueued:   next reference in queue (or this if last)
     *    Inactive:   this
     */
    @SuppressWarnings("rawtypes")
    Reference next; // 引用所处的状态不同时，该属性保存了不同的信息
    
	// ...
    
    /**
     * 获取当前引用所指向的对象的方法，如果所指向对象已经被 GC 回收，那么返回 null
     */
    public T get() {
        return this.referent;
    }

    /**
     * 清除该引用所指向的对象，该方法会在 GC 回收该引用指向的对象后被 GC 调用，
     * 之后，通过该引用对象的 get 方法得到的返回值为 null, 该方法不应该被程序员主动调用
     */
    public void clear() {
        this.referent = null;
    }

    /* -- Queue operations -- */

    /**
     * 判断当前引用是否已经进入对应的引用队列，
     * 如果构造该引用对象时没有指定对应的引用队列，那么该方法始终返回 false
     */
    public boolean isEnqueued() {
        return (this.queue == ReferenceQueue.ENQUEUED);
    }

    /**
     * 如果当前引用对象的引用队列属性（构造时由参数指定）不为 null, 
     * 那么当这个引用所指向的对象被 GC 回收之后会由 GC 调用这个方法，
     * 代表将该引用进入对应的引用队列（即该引用指向的对象被回收）
     */
    public boolean enqueue() {
        return this.queue.enqueue(this);
    }

    /* -- Constructors -- */
    Reference(T referent) {
        this(referent, null);
    }

    Reference(T referent, ReferenceQueue<? super T> queue) {
        this.referent = referent;
        this.queue = (queue == null) ? ReferenceQueue.NULL : queue;
    }
}
```

我们在 `Reference` 类中的 `enqueue` 方法（这个方法本身会被 GC 线程调用）中发现其直接调用了对应引用队列（`ReferenceQueue`）的 `enqueue` 方法，我们来看看 `ReferenceQueue` 类的这个方法：

```java
public class ReferenceQueue<T> {

    /**
     * Constructs a new reference-object queue.
     */
    public ReferenceQueue() { }

    // ...

    static private class Lock { };
    private Lock lock = new Lock();
    private volatile Reference<? extends T> head = null;
    private long queueLength = 0;

    // 引用对象本身入队列的过程就是一个向单向链表中插入节点的过程
    boolean enqueue(Reference<? extends T> r) { /* Called only by Reference class */
        synchronized (lock) { // 保证线程安全
            // Check that since getting the lock this reference hasn't already been
            // enqueued (and even then removed)
            ReferenceQueue<?> queue = r.queue;
            if ((queue == NULL) || (queue == ENQUEUED)) {
                return false;
            }
            assert queue == this;
            r.queue = ENQUEUED; // 更新引用入队状态
           	// 前插法插入链表节点
            r.next = (head == null) ? r : head;
            head = r;
            queueLength++;
            if (r instanceof FinalReference) {
                sun.misc.VM.addFinalRefCount(1);
            }
            lock.notifyAll();
            return true;
        }
    }

    /**
     * 返回当前引用队列中的第一个引用对象，如果不存在则返回 null
     * 该方法不会阻塞线程
     */
    public Reference<? extends T> poll() {
        if (head == null)
            return null;
        synchronized (lock) {
            return reallyPoll();
        }
    }

    /**
     * 返回当前引用队列中第一个可用的引用对象，如果没有，则阻塞线程一定时间（参数指定）
     * 阻塞时间过后，如果当前队列中仍然没有可用的引用对象，那么抛出中断异常（InterruptedException）
     */
    public Reference<? extends T> remove(long timeout)
        throws IllegalArgumentException, InterruptedException
    {
        if (timeout < 0) {
            throw new IllegalArgumentException("Negative timeout value");
        }
        synchronized (lock) {
            Reference<? extends T> r = reallyPoll();
            if (r != null) return r;
            long start = (timeout == 0) ? 0 : System.nanoTime();
            for (;;) {
                lock.wait(timeout);
                r = reallyPoll();
                if (r != null) return r;
                if (timeout != 0) {
                    long end = System.nanoTime();
                    timeout -= (end - start) / 1000_000;
                    if (timeout <= 0) return null;
                    start = end;
                }
            }
        }
    }

    /**
     * 阻塞调用线程，直到当前引用队列中存在可用的引用对象，将该引用对象从引用队列中移除并返回该引用对象
     */
    public Reference<? extends T> remove() throws InterruptedException {
        return remove(0);
    }

}
```

利用注释和源代码，我们就可以将整个过程的逻辑串起来了：

**GC 线程回收对象 -> 将相关指向这个对象的引用加入到其引用队列（如果有）-> 更新引用入队状态（`isEnqueued` 方法返回 true）-> 在 Java 代码中可以得到引用队列中的已经入队的引用（即得到要回收对象的对应引用对象，作为对象回收的一个通知）。**

下面看一个小例子，利用引用队列来得知回收的对象，我们在上一节的代码中新建一个静态内部类 `ReferenceQueueTest`：

```java
// 引用队列测试类
static class ReferenceQueueTest {

    ReferenceQueue<byte[]> referenceQueue = new ReferenceQueue<>();

    // 对象回收时的引用通知测试
    void testReferenceNotify() {
        WeakReference<byte[]> weakReference = new WeakReference<>(new byte[1024], referenceQueue);
        // 后面的 ReferenceQueue.remove 方法会阻塞调用线程，因此开子线程进行操作
        Thread thread = new Thread(() -> {
            try {
                for (Reference pr; (pr = referenceQueue.remove()) != null; ) {
                    System.out.println(pr + " 引用所指向的对象被回收!");
                }
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        });
        /* 
			 因为 ReferenceQueue 对象的 remove 方法是阻塞线程的，因此子线程需设置守护线程，
			 否则如果 ReferenceQueue 中没有可取出的引用对象会导致线程一直阻塞，程序不能退出
			*/
        thread.setDaemon(true);
        thread.start();
        // 启动垃圾回收动作，将弱引用指向的对象回收
        System.gc();
    }
}
```

在 `main` 方法中新建该内部类对象并且调用 `testReferenceNotify` 方法：

![](C:\Users\MAIBENBEN\Desktop\blog\详解 Java 4 种引用\4.png)

可以看到，当弱引用指向的对象被回收之后，我们成功的从该弱引用对象中的引用对象中得到了该弱引用对象，即完成了对象回收的监视过程。

OK。到这里，对 Java 中四种引用和引用队列的介绍就结束了，相信通过例子和分析源码的过程你对相关知识有了更进一步的了解。

如果文章中有什么不正确的地方，还请多多指点，如果觉得本篇文章对您有帮助，请不要吝啬您的赞。

谢谢观看。。。