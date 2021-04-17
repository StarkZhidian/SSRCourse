package main;

import java.util.LinkedList;
import java.util.Locale;

/**
 * Create by StarkZhidian on 2019-01-18
 * <p>
 * 字符串和其它数据的转换工具类
 */
public class StringUtils {


    public static String format( String format,  Object... args) {
        try {
            return String.format(Locale.CHINA, format, args);
        } catch (Exception e) {
            return "";
        }
    }

    public static String valueOf(int value) {
        try {
            return String.valueOf(value);
        } catch (Exception e) {
            return "";
        }
    }

    public static boolean string2Bool(String value) {
        try {
            return Boolean.valueOf(value);
        } catch (Exception e) {
            return false;
        }
    }

    public static byte string2Byte(String value) {
        try {
            return Byte.valueOf(value);
        } catch (Exception e) {
            return 0;
        }
    }

    public static char string2Char(String value) {
        try {
            return value.charAt(0);
        } catch (Exception e) {
            return ' ';
        }
    }

    public static short string2Short(String value) {
        try {
            return Short.valueOf(value);
        } catch (Exception e) {
            return 0;
        }
    }

    public static int string2Int(String s) {
        try {
            return Integer.valueOf(s);
        } catch (Exception e) {
            return 0;
        }
    }

    public static float string2Float(String value) {
        try {
            return Float.valueOf(value);
        } catch (Exception e) {
            return 0;
        }
    }

    public static long string2Long(String value) {
        try {
            return Long.valueOf(value);
        } catch (Exception e) {
            return 0;
        }
    }

    public static double string2Double(String value) {
        try {
            return Double.valueOf(value);
        } catch (Exception e) {
            return 0;
        }
    }

    /**
     * 计算 content 中以 end 开始往前连续转义字符 \ 的个数
     *
     * @param content
     * @param end
     * @return
     */
    public static int calculatePreviousTransferCharCount(String content, int end) {
        int start = end;
        while (start >= 0 && content.charAt(start) == '\\') {
            start--;
        }
        return end - start;
    }

    /**
     * 计算 content 中以 end 开始往前连续转义字符 \ 的个数
     *
     * @param content
     * @param end
     * @return
     */
    public static int calculatePreviousTransferCharCount(StringBuilder content, int end) {
        int start = end;
        while (start >= 0 && content.charAt(start) == '\\') {
            start--;
        }
        return end - start;
    }

    /**
     * compare str1 and str2, if the integer value of str1 greater than integer value of str2, return plus,
     * else if the integer value of str1 same as the integer value of str2, return 0,
     * else return negative
     */
    public static int compareStringByInteger( String str1,  String str2) {
        int value1;
        int value2;
        try {
            value1 = Integer.parseInt(str1);
            value2 = Integer.parseInt(str2);
        } catch (Exception e) {
            return 0;
        }
        return value1 - value2;
    }

    /**
     * 反向查找字符串，返回 child 字符串在 parent 字符串中第一次反向出现的位置
     *
     * @param parent
     * @param child
     * @param reverseFromIndex 查找开始索引，从后向前
     * @return 字串在父串的位置，如果未查找到，则返回 -1
     * eg: String parent = "hehehelloworld", child = "he";
     * invoke reverseIndexOf(parent, child, parent.length()), result = 4
     */
    public static int reverseIndexOf( String parent,  String child, int reverseFromIndex) {
        if (TextUtils.isEmpty(parent) || TextUtils.isEmpty(child) || child.length() > parent.length() ||
                reverseFromIndex <= 0) {
            return -1;
        }
        int childLen = child.length();
        int j;
        reverseFromIndex = Math.min(reverseFromIndex, parent.length());
        int currentIndex = reverseFromIndex - childLen;
        for (int i = 0; currentIndex >= 0; i++) {
            if (i >= childLen) {
                return currentIndex;
            }
            // 子串中第 i 个字符和父串对应字符不匹配
            if (parent.charAt(currentIndex + i) != child.charAt(i)) {
                j = currentIndex + i;
                // 父串后移，直到找到和字串中第 i 个字符相等的字符
                while (j >= 0 && parent.charAt(j) != child.charAt(i)) {
                    j--;
                }
                // 更新父串中开始查找的下标值
                currentIndex = j - i;
                i = -1;
            }
        }
        return -1;
    }

    /**
     * 反转字符串，不影响源字符串，返回反转后的字符串
     *
     * @param sourceStr
     * @return
     */
    public static String reverseStr( String sourceStr) {
        if (TextUtils.isEmpty(sourceStr)) {
            return sourceStr;
        }
        char[] chars = sourceStr.toCharArray();
        int mid = chars.length / 2, tIndex;
        char t;
        for (int i = 0; i < mid; i++) {
            t = chars[i];
            chars[i] = chars[tIndex = chars.length - 1 - i];
            chars[tIndex] = t;
        }
        return new String(chars);
    }

    /**
     * 从 fromIndex 开始查找子串 child 在父串 parent 中出现的位置记录
     *
     * @param parent
     * @param child
     * @param fromIndex
     * @return
     */
    public static LinkedList<Integer> getChildIndexList( String parent,  String child,
                                                        int fromIndex) {
        LinkedList<Integer> result = new LinkedList<>();
        if (TextUtils.isEmpty(parent) || TextUtils.isEmpty(child)) {
            return result;
        }
        fromIndex = Math.max(0, Math.min(parent.length(), fromIndex));
        int index = fromIndex, childLen = child.length();
        while ((index = parent.indexOf(child, index)) != -1) {
            result.add(index);
            index += childLen;
        }
        return result;
    }

    /**
     * 从 fromIndex 开始查找子串 child 在父串 parent 中出现的次数
     *
     * @param parent
     * @param child
     * @param fromIndex
     * @return
     */
    public static int getChildIndexCount( String parent,  String child,
                                         int fromIndex) {
        if (TextUtils.isEmpty(parent) || TextUtils.isEmpty(child)) {
            return 0;
        }
        fromIndex = Math.max(0, Math.min(parent.length(), fromIndex));
        int result = 0;
        int index = fromIndex, childLen = child.length();
        while ((index = parent.indexOf(child, index)) != -1) {
            result++;
            index += childLen;
        }
        return result;
    }

    /**
     * 获取 s 中换行符的个数
     *
     * @param s
     * @return s 中换行符的个数
     */
    public static int getChangeLineCharCount(CharSequence s) {
        int res = 0;
        if (s != null) {
            for (int i = 0; i < s.length(); i++) {
                res += s.charAt(i) == '\n' ? 1 : 0;
            }
        }
        return res;
    }

    /**
     * 获取字符串中空白字符（'\t' '\n' ' '）的个数
     * @param charSequence
     * @return
     */
    public static int getWhiteCharCount(CharSequence charSequence) {
        int length = charSequence.length();
        int res = 0;
        char ch;
        for (int i = 0; i < length; i++) {
            ch = charSequence.charAt(i);
            if (ch == '\t' || ch == '\n' || ch == ' ') {
                res++;
            }
        }
        return res;
    }

    public static void main(String[] args) {

    }
}
