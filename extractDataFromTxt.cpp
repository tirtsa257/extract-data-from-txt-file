#include <stdio.h>
#include <xstring>

typedef struct dict_entry_s
{
    const char *key;
    int value;
} dict_entry_s;

typedef struct dict_s
{
    int len;
    int cap;
    dict_entry_s *entry;
} dict_s, *dict_t;

int countMaxK = 0;
int maxK = 0;
int uniqCount = 0, max = 0, maxWithOut = 0;
const char * maxWord;
const char* maxWordWithOut;

int main()
{
    char line[150], word[50];
    int sentences[150];
    int countWords = 0, countLines = 0, countSentences = 0, countWordsSentencice = 0;
    FILE *fp;
    dict_t dictonary = dict_new();
    fp = fopen("file.txt", "r");

    void dict_add(dict_t dict, const char *key);
    dict_t dict_new(void);
    void dict_free(dict_t dict);
    bool endSentence(char *word);
    void containK(char *word);
    void sentence(int *sentences);

    while (fgets(line, 150, fp))
    {
        countLines++;
        while (sscanf(line, "%s", word) != EOF)
        {
            countWords++;
            countWordsSentencice++;
            dict_add(dictonary, word);
            if (endSentence(word))
                sentences[countSentences++] = countWordsSentencice;
            containK(word);
        }
    }
    sentence(sentences);

    printf("Count of lines:%d", countLines);
    printf("Count of words:%d", countWords);
    printf("The lengh of sentences:%d", countLines);
    printf("The longest word sequence in a text that does not contain the letter k:%d", maxK);

    fclose(fp);
    return 0;
}

typedef struct dict_entry_s
{
    const char *key;
    int value;
    int color;
} dict_entry_s;

typedef struct dict_s
{
    int len;
    int cap;
    dict_entry_s *entry;
} dict_s, *dict_t;

int dict_find_index(dict_t dict, const char *key)
{
    for (int i = 0; i < dict->len; i++)
    {
        if (!strcmp(dict->entry[i].key, key))
        {
            if (!strcmp(dict->entry[i].key, key))
            {

                return i;
            }
        }
        return -1;
    };
}
void dict_end(dict_t dict)
{
    printf("Color names that appear in the text:");
    for (int i = 0; i < dict->len; i++)
    {
        //color
        if (dict->entry[i].color > 0)
        {
            printf("%s - %d", dict->entry[i].key, dict->entry[i].value);
        }
        //unique
        if (dict->entry[i].value == 1)
            uniqCount++;
        //popoulate
        if (dict->entry[i].value > max)
        {
            if (!isSyntacticWord(dict->entry[i].key))
            {
                max = dict->entry[i].value;
                maxWithOut = dict->entry[i].value;
                maxWordWithOut = dict->entry[i].key;
                maxWord = dict->entry[i].key;
            }
            else
            {
                max = dict->entry[i].value;
                maxWord = dict->entry[i].key;
            }
        }
    }
    printf("\nThe amount of unique words in the file: %d \n", uniqCount);
    printf("The most popular word in the text %s and the popular wordMost that is not a word with syntactic meaning in English %s \n", maxWord, maxWordWithOut);
    dict_free(dict);
}

void dict_add(dict_t dict, const char *key)
{
    int idx = dict_find_index(dict, key);
    if (idx != -1)
    {
        dict->entry[idx].value += 1;
        if (dict->entry[idx].color != 0)
            dict->entry[idx].color += 1;
        return;
    }
    if (dict->len == dict->cap)
    {
        dict->cap *= 2;
        dict->entry = (dict_entry_s *)realloc(dict->entry, dict->cap * sizeof(dict_entry_s));
    }
    dict->entry[dict->len].key = strdup(key);
    dict->entry[dict->len].value = dict->entry[dict->len].value = 1;
    if (isColorWord(key))
        dict->entry[dict->len].color = dict->entry[dict->len].value = 1;
    dict->len++;
};

dict_t dict_new(void)
{
    dict_s proto = {0, 10, (dict_entry_s *)malloc(10 * sizeof(dict_entry_s))};
    dict_t d = (dict_t)malloc(sizeof(dict_s));
    *d = proto;
    return d;
};

void dict_free(dict_t dict)
{

    free(dict->entry);
    free(dict);
    free(dict);
}

bool isColorWord(const char *word)
{
    const char *colors[] = {"green", "yellow", "blue"};
    int len = sizeof(colors) / sizeof(colors[0]);

    for (int i = 0; i < len; ++i)
    {
        if (strcmp(colors[i], word) == 0)
            return true;
    }
    return false;
}

bool endSentence(char *word)
{
    const char *const Unusual[] = {"Mr.", "Ms.", "Mrs.", "sr.", "Ave.", "Rd."};
    int len = sizeof(Unusual) / sizeof(Unusual[0]);

    if (strtok(word, "!") || strtok(word, "?") == 0)
        return true;
    if (strtok(word, ".") != 0)
        return false;
    for (int i = 0; i < len; ++i)
    {
        if (strcmp(Unusual[i], word) == 0)
            return false;
    }
    return true;
}

void cntainK(char *word)
{
    if (strtok(word, "k") == 0)
    {
        countMaxK += 1;
        if (countMaxK > maxK)
            maxK = countMaxK;
    }
    else
        countMaxK = 0;
}

bool isSyntacticWord(const char *word)
{
    const char *const list[] = {"the", "that", "don't", "are", "am", "is"};
    int len = sizeof(list) / sizeof(list[0]);

    for (int i = 0; i < len; ++i)
    {
        if (strcmp(list[i], word) == 0)
            return true;
    }
    return false;
}

void sentence(int *sentences)
{
    int i, max = 0, sum = 0;
    for (i = 0; sentences[i]; ++i)
    {
        if (sentences[i] > max)
            max = sentences[i];
        sum += sentences[i];
    }
    printf("The average sentence length is:%d and Maximum sentence length is %d", sum / i, max);
}
