#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int count_letters(string Text);
int count_words(string Text);
int count_sentences(string Text);
void calc_Grade(int letters, int words, int sentences);

int main(void)
{
    string Text = get_string("Text: ");
    int letters = count_letters(Text);
    int words = count_words(Text);
    int sentences = count_sentences(Text);
    printf("%i letters\n",letters);
    printf("%i words\n",words);
    printf("%i sentences\n",sentences);
    calc_Grade(letters, words, sentences);
}

int count_letters(string Text)
{
    int letters = 0;
    for(int i = 0, n = strlen(Text); i < n; i++)
    {
        if (isalpha(Text[i]) != 0)
        {
            letters++;
        }
    }
    return letters;
}

int count_words(string Text)
{
    int words = 0;
    for(int i = 0, n = strlen(Text); i < n; i++)
    {
        if (isspace(Text[i]) != 0)
        {
            words++;
        }
    }
    return words+1;
}

int count_sentences(string Text)
{
    int sentences = 0;
    for(int i = 0, n = strlen(Text); i < n; i++)
    {
        if (Text[i] == '.' || Text[i] == '!' || Text[i] == '?')
        {
            sentences++;
        }
    }
    return sentences;
}

void calc_Grade(int letters, int words, int sentences)
{
    int Grade;
    double index = (letters / (double)words * 100) * 0.0588 - (sentences / (double)words * 100) * 0.296 - 15.8;

    if (index - (int)index >= 0.5)
    {
        Grade = (int)index + 1;
    }
    else
    {
        Grade = (int)index;
    }

    if (Grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (Grade > 1 && Grade < 16)
    {
        printf("Grade %i\n",Grade);
    }
    else
    {
        printf("Grade 16+\n");
    }
}

