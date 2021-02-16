# Translator

Develop a Translator class to save bilingual word pairs and then translate words from one language to another using the pairs you have already added:
```cpp
class Translator {
public:
  void Add(string_view source, string_view target);
  string_view TranslateForward(string_view source) const;
  string_view TranslateBackward(string_view target) const;

private:
  // ...
};
```
More specifically, an object t of type Translator must allow the following actions:

1. Created with the default constructor. In this case, the translation memory is empty.
2. Adding a bilingual pair: t.Add (source, target). After such a call, the word source in language 1 is considered to correspond to the word target in language 2. The strings passed to the Add method can be destroyed before the object t.
3. Translation from language 1 to language 2: t.TranslateForward (source). If there has already been a call to t.Add (source_copy, target) for some string target and a string source_copy equal to (or is) source, then target must be returned. If there was no such call, an empty string should be returned. If there were several such calls, you need to return target for the last one.
4. Translation from language 2 to language 1: t.TranslateBackward (target). If there has already been a call to t.Add (source, target_copy) for some string source and a string target_copy equal to (or is) target, then source must be returned. If there was no such call, an empty string should be returned. If there were several such calls, you need to return source for the last one.

## Limitations

Each line must be stored in an instance of the Translator class at most once. If this limit is violated, you will receive a "Memory limit exceeded" error.
