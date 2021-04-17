package main;

import java.lang.annotation.Annotation;
import java.lang.reflect.Method;

@ReturnRequireAnnotationRuntime
@ReturnRequireAnnotationRuntimeNoInherited
public class Main {

    static class MainSub extends Main {
        @Override
        public Object string2Integer(String s) {
            return super.string2Integer(s);
        }

        @Override
        public Long string2Long(String s) {
            return super.string2Long(s);
        }

        @Override
        public Float string2Float(String s) {
            return super.string2Float(s);
        }

        @Override
        public Object string2Object(String s) {
            return super.string2Object(s);
        }
    }

    void printAnnotation(String prefixInfo) throws NoSuchMethodException {
        if (prefixInfo != null && !"".equals(prefixInfo)) {
            System.out.println(prefixInfo);
        }
        Method string2Integer = getClass().getDeclaredMethod("string2Integer", String.class);
        if (string2Integer != null) {
            ReturnRequireAnnotationSourceCode annotation =
                    string2Integer.getAnnotation(ReturnRequireAnnotationSourceCode.class);
            System.out.println(annotation);
            if (annotation != null) {
                System.out.println("returnRequireType: " + annotation.returnRequire());
            }
        }

        Method string2Long = getClass().getDeclaredMethod("string2Long", String.class);
        if (string2Long != null) {
            ReturnRequireAnnotationInClass annotation =
                    string2Long.getAnnotation(ReturnRequireAnnotationInClass.class);
            System.out.println(annotation);
            if (annotation != null) {
                System.out.println("returnRequireType: " + annotation.returnRequire());
            }
        }

        Method string2Float = getClass().getDeclaredMethod("string2Float", String.class);
        if (string2Float != null) {
            ReturnRequireAnnotationRuntime annotation =
                    string2Float.getAnnotation(ReturnRequireAnnotationRuntime.class);
            System.out.println(annotation);
            if (annotation != null) {
                System.out.println("returnRequireType: " + annotation.returnRequire());
            }
        }

        Method string2Object = getClass().getDeclaredMethod("string2Object", String.class);
        if (string2Object != null) {
            ReturnRequireAnnotationRuntime annotation =
                    string2Object.getAnnotation(ReturnRequireAnnotationRuntime.class);
            System.out.println(annotation);
            if (annotation != null) {
                System.out.println("returnRequireType: " + annotation.returnRequire());
            }
        }
    }

    public static void main(String[] args) throws Exception {
        System.out.println("使用带有 Inherited 注解: ");
        if (Main.class.isAnnotationPresent(ReturnRequireAnnotationRuntime.class)) {
            Annotation annotation = Main.class.getAnnotation(ReturnRequireAnnotationRuntime.class);
            System.out.println(annotation);
        }
        if (MainSub.class.isAnnotationPresent(ReturnRequireAnnotationRuntime.class)) {
            Annotation annotation = MainSub.class.getAnnotation(ReturnRequireAnnotationRuntime.class);
            System.out.println(annotation);
        }
        System.out.println("使用非带有 Inherited 注解: ");
        if (Main.class.isAnnotationPresent(ReturnRequireAnnotationRuntimeNoInherited.class)) {
            Annotation annotation = Main.class.getAnnotation(ReturnRequireAnnotationRuntimeNoInherited.class);
            System.out.println(annotation);
        }
        if (MainSub.class.isAnnotationPresent(ReturnRequireAnnotationRuntimeNoInherited.class)) {
            Annotation annotation = MainSub.class.getAnnotation(ReturnRequireAnnotationRuntimeNoInherited.class);
            System.out.println(annotation);
        }

        new Main().printAnnotation("\n类 main.Main: ");
        new MainSub().printAnnotation("\n类 MainSub: ");
    }


    @ReturnRequireAnnotationSourceCode(returnRequire = Integer.class)
    public Object string2Integer(String s) {
        try {
            return Integer.parseInt(s);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return 0;
    }

    @ReturnRequireAnnotationInClass(returnRequire = Long.class)
    public Long string2Long(String s) {
        try {
            return Long.parseLong(s);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return 0L;
    }

    @ReturnRequireAnnotationRuntime(returnRequire = Float.class)
    public Float string2Float(String s) {
        try {
            return Float.parseFloat(s);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return 0f;
    }

    @ReturnRequireAnnotationRuntime
    public Object string2Object(String s) {
        return s;
    }

}
