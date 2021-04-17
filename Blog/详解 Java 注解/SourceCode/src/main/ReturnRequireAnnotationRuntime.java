package main;

import java.lang.annotation.*;

@Target(value = {ElementType.TYPE, ElementType.METHOD})
@Retention(value = RetentionPolicy.RUNTIME)
@Inherited
public @interface ReturnRequireAnnotationRuntime {

    Class returnRequire() default Object.class;
}
