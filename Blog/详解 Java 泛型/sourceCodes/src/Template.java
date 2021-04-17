/**
 * 一个使用泛型的简单例子
 */
public class Template<X extends A> {
    private X obj;

    public X getObj() {
        return obj;
    }

    public void setObj(X obj) {
        this.obj = obj;
    }
}
