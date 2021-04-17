package main;

import java.lang.annotation.*;

@Target(value = {ElementType.TYPE, ElementType.METHOD})
@Retention(value = RetentionPolicy.CLASS)
public @interface ReturnRequireAnnotationInClass {

    Class returnRequire() default Object.class;
}
