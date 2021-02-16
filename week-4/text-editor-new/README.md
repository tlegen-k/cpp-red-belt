# Text Editor

Consider a simplified text editor that supports the following set of commands:

-    Moves the cursor left and right one position.
-    Enter a character at the current cursor position (Insert).
-    Copying a piece of text starting at the current cursor position to the clipboard (Copy).
-    Cutting a piece of text is similar to copying and then removing the copied characters from the text (Cut).
-    Paste the contents of the clipboard at the current cursor position (Paste).

These commands are indeed supported by almost any text editor. There are also standard rules for teams that determine their effect:

-    If the editor contains text of length n characters, then the cursor can be in one of (n + 1) possible positions. For example, let's mark the cursor with a pipe | (we will use this notation in what follows), then in the text abc the cursor can be located in 4 positions: | abc, a | bc, ab | c, abc |. Therefore, the Left command has no effect when the cursor is at the beginning of the text, and Right has no effect when the cursor is at the end. In particular, neither Left nor Right has an effect when the editor contains no text.
-    The entered character is located at the cursor position, shifting the cursor and all text to the right of it one position to the right. Similarly, when inserting a fragment of length n, the cursor and the text to the right of it move n positions to the right. The table below shows examples to demonstrate this rule.

|Before insertion| Inserted character / fragment to be inserted| After insertion|
|---       |-----   |-----|
| \|       | a      | a\| |
| ab\|     | c      | abc\| |
| \|bc     | a      | a\|bc |
| \| world | hello_ | hello_world\| |
| hello_\| | world  | hello_world\| |
| 123\|78  | 456    | 123456\|78 |


- The clipboard is initially empty. Inserting an empty section has no effect. The contents of the buffer are not discarded after pasting, but remain unchanged until the next Copy or Cut command. Copying or cutting a piece of zero length has no effect on the text, but empties the clipboard. The cursor does not move when copying or cutting text. For example, after cutting out a fragment of three characters from the text ab | cdef, we get the text ab | f.
-
You have to implement the "core" of a text editor that supports all described operations in the form of an Editor class with the following interface:

```cpp
class Editor {
public:
  Editor();
  void Left();   // сдвинуть курсор влево
  void Right();  // сдвинуть курсор вправо
  void Insert(char token);   // вставить символ token
  void Copy(size_t tokens);  // cкопировать
                             // не более tokens символов,
                             // начиная с текущей позиции курсора
  void Cut(size_t tokens);  // вырезать не более tokens символов,
                            // начиная с текущей позиции курсора
  void Paste();  // вставить содержимое буфера
                 // в текущую позицию курсора
  string GetText() const;  // получить текущее содержимое
                           // текстового редактора
};
```

As you can see, each described command has a method associated with the Editor class. Also introduced the GetText () method, which allows you to get the current content of the editor as a string. In the comments to the Cut (size_t tokens) and Copy (size_t tokens) methods, it is indicated that a fragment of no more than tokens characters is placed on the clipboard - this means that if there are less than tokens characters to the right of the cursor, the Cut () and Copy () should cut / copy all characters to the right.

## Limitations

An implementation of the Editor class should process 10 ^ 6 requests in no more than 1 second. At the same time it is guaranteed that:

-     text length never exceeds 10 ^ 6 characters;
-     the Copy () and Cut () methods copy / cut no more than 10 ^ 6 characters in total;
-     the GetText () method is called once in each of the tests.

## Example

### Code
```cpp
int main() {
  Editor editor;
  const string text = "hello, world";
  for (char c : text) {
    editor.Insert(c);
  }
  // Текущее состояние редактора: `hello, world|`
  for (size_t i = 0; i < text.size(); ++i) {
    editor.Left();
  }
  // Текущее состояние редактора: `|hello, world`
  editor.Cut(7);
  // Текущее состояние редактора: `|world`
  // в буфере обмена находится текст `hello, `
  for (size_t i = 0; i < 5; ++i) {
    editor.Right();
  }
  // Текущее состояние редактора: `world|`
  editor.Insert(',');
  editor.Insert(' ');
  // Текущее состояние редактора: `world, |`
  editor.Paste();
  // Текущее состояние редактора: `world, hello, |`
  editor.Left();
  editor.Left();
  //Текущее состояние редактора: `world, hello|, `
  editor.Cut(3); // Будут вырезаны 2 символа
  // Текущее состояние редактора: `world, hello|`
  cout << editor.GetText();
}
```
