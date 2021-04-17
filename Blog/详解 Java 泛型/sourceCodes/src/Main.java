import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.List;

public class Main {

    public static void main(String[] args) {
        Template<B> template = new Template<>();
        template.setObj(new B());
        B b = template.getObj();

        List<? extends A> list = new ArrayList<>();
        // 无需强制类型转换
        A a = list.get(0);
        // 无需强制类型转换
        Object obj = list.get(0);
        // 需要强制类型转换
        B b = (B) list.get(0);
    }
}