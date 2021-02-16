#include <list>

#include "test_runner.h"
using namespace std;

class Editor {
public:
    Editor(): text_(), it_(text_.end()), buffer_() {}

    //- Moving cursor
    void Left()
    {
        if (it_ != text_.begin() && !text_.empty())
        {
            it_--;
        }
    }
    void Right()
    {
        if (it_ != text_.end() && !text_.empty())
        {
            it_++;
        }
    }

    //- Input token at current position of cursor
    void Insert(char token)
    {
        //- Inserting empty token should not have effect
        if (token != '\0')
        {
            //- inserts value before pos & doesn't invalidate iterators
            text_.insert(it_, token);
        }
    }
    void Cut(size_t tokens)
    {
        const auto pos = it_;
        buffer_.clear();
        size_t n = tokens;

        while((it_ != end(text_)) && (n > 0))
        {
            buffer_.push_back(*it_);
            it_++;
            n -= 1;
        }
        text_.erase(pos, it_);

    }
    void Copy(size_t tokens)
    {
        const auto pos = it_;
        buffer_.clear();
        size_t n = tokens;

        while((it_ != end(text_)) && (n > 0))
        {
            buffer_.push_back(*it_);
            it_++;
            n -= 1;

        }
        it_ = pos;
    }

    //- Cursor should be placed after input
    void Paste()
    {
        text_.insert(it_, begin(buffer_),end(buffer_));

        //- For some reason advancing does not work
//        std::advance(it_,buffer_.size());

        for (int i = 0; i << buffer_.size(); i++) it_++;
    }

    string GetText() const
    {
        string result;
        for(auto it = begin(text_); it != end(text_); it++)
        {
            result.push_back(*it);
        }
        return result;
    }
    string GetBuffer() const
    {
        string result;
        for(auto it = begin(buffer_); it != end(buffer_); it++)
        {
            result.push_back(*it);
        }
        return result;
    }
    char CurrentPos()
    {
        return *it_;
    }
private:
    list<char> text_;
    list<char> buffer_;
    list<char>::iterator it_;
};

void TypeText(Editor& editor, const string& text) {
    for(char c : text) {
        editor.Insert(c);
    }
}
void TestBasic() {
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
    cout << "Initial pos = " << editor.CurrentPos() << endl;
    editor.Cut(7);

    // Текущее состояние редактора: `|world`

    cout << "Text after Cut(7):" << editor.GetText() << endl;
    cout << "pos = " << editor.CurrentPos() << endl;
    // в буфере обмена находится текст `hello, `
    cout << "Buffer after Cut(7):" << editor.GetBuffer() << endl;
    for (size_t i = 0; i < 5; ++i) {
        editor.Right();
    }
    // Текущее состояние редактора: `world|`
    cout << "pos = " << editor.CurrentPos() << endl;
    editor.Insert(',');
    editor.Insert(' ');
    // Текущее состояние редактора: `world, |`

    cout << "Text after Insert 2 times:" << editor.GetText() << endl;
    cout << "pos = " << editor.CurrentPos() << endl;

    cout << "Buffer before Paste:" << editor.GetBuffer() << endl;

    editor.Paste();

    // Текущее состояние редактора: `world, hello, |`
    cout << "Text after Paste:" << editor.GetText() << endl;
    cout << "pos = " << editor.CurrentPos() << endl;
    editor.Left();
    cout << "pos = " << editor.CurrentPos() << endl;
    editor.Left();
    cout << "pos = " << editor.CurrentPos() << endl;
    //Текущее состояние редактора: `world, hello|, `
    editor.Cut(3); // Будут вырезаны 2 символа
    cout << "Text after pasting:" << editor.GetText() << endl;
    cout << "pos = " << editor.CurrentPos() << endl;
    // Текущее состояние редактора: `world, hello|`
    cout << editor.GetText();

    ASSERT_EQUAL(editor.GetText(), "world, hello");
}
void TestEditing() {
    {
        Editor editor;

        const size_t text_len = 12;
        const size_t first_part_len = 7;
        TypeText(editor, "hello, world");
        //- Moving cursor to the beginning
        for(size_t i = 0; i < text_len; ++i) {
            editor.Left();
        }
        //- Cut "hello,"
        editor.Cut(first_part_len);

        for(size_t i = 0; i < text_len - first_part_len; ++i) {
            editor.Right();
        }
        TypeText(editor, ", ");

        editor.Paste();

        editor.Left();
        editor.Left();

        editor.Cut(3);
        ASSERT_EQUAL(editor.GetText(), "world, hello");
    }
    {
        Editor editor;

        TypeText(editor, "misprnit");
        editor.Left();
        editor.Left();
        editor.Left();
        editor.Cut(1);
        editor.Right();
        editor.Paste();

        ASSERT_EQUAL(editor.GetText(), "misprint");
    }
}

void TestReverse() {
    Editor editor;

    const string text = "esreveR";
    for(char c : text) {
        editor.Insert(c);
        editor.Left();
    }

    ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
    Editor editor;
    ASSERT_EQUAL(editor.GetText(), "");

    editor.Left();
    editor.Left();
    editor.Right();
    editor.Right();
    editor.Copy(0);
    editor.Cut(0);
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
    Editor editor;

    editor.Paste();
    TypeText(editor, "example");
    editor.Left();
    editor.Left();
    editor.Paste();
    editor.Right();
    editor.Paste();
    editor.Copy(0);
    editor.Paste();
    editor.Left();
    editor.Cut(0);
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "example");
}

int main() {
    TestRunner tr;
   RUN_TEST(tr, TestBasic);
   RUN_TEST(tr, TestEditing);
   RUN_TEST(tr, TestReverse);
   RUN_TEST(tr, TestNoText);
   RUN_TEST(tr, TestEmptyBuffer);
    return 0;
}
