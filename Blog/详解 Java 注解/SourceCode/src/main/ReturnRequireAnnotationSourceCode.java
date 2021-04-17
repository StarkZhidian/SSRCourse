package main;

import java.lang.annotation.*;

@Target(value = {ElementType.TYPE, ElementType.METHOD})
@Retention(value = RetentionPolicy.SOURCE)
public @interface ReturnRequireAnnotationSourceCode {

    Class returnRequire() default Object.class;
}
