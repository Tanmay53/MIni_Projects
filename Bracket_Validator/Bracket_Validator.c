#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h> 
#include <unistd.h>

int clear_icanon(int canonical)
{
  struct termios settings;
  int result;
  result = tcgetattr (STDIN_FILENO, &settings);
  if (result < 0)
    {
      perror ("error in tcgetattr");
      return 0;
    }

    if(canonical)
    {
        settings.c_lflag |= ICANON;
    }
    else
    {
        settings.c_lflag &= ~ICANON;
    }

  result = tcsetattr (STDIN_FILENO, TCSANOW, &settings);
  if (result < 0)
    {
      perror ("error in tcsetattr");
      return 0;
   }
  return 1;
}

typedef struct stack
{
    char data;
    int index;
    struct stack *next;
} node;
node *top = NULL, *temp;

void push(char key, int place)
{
    node *newNode;
    newNode = (node*)malloc(sizeof(node));
    newNode->data = key;
    newNode->index = place;
    newNode->next = top;
    top = newNode;
}

char pop()
{
    if(top == NULL)
    {
        return 0;//Empty
    }
    else
    {
        char key;
        temp = top;
        key = top->data;
        top = top->next;
        free(temp);
        return key;
    }
}

char peep()
{
    if(top == NULL)
    {
        return 1;//Empty
    }
    else
    {
        return top->data;
    }
}

int isEmpty()
{
    if(top == NULL)
    {
        return 1;//Empty
    }
    else
    {
        return 0;//Filled
    }
}

int checkBrackets(char str[100010])
{
    unsigned long int length = strlen(str);
    for(int i = 0; i < length; i++)
    {
        if((str[i] == '(') || (str[i] == '{') || (str[i] == '['))
        {
            push(str[i], (i + 1));
        }
        else if((str[i] == ')') || (str[i] == '}') || (str[i] == ']'))
        {
            if(isEmpty())
            {
                return i+1;
            }
            char head = pop();
            if(((head == '(') && (str[i] != ')')) || ((head == '{') && (str[i] != '}')) || ((head == '[') && (str[i] != ']')))
            {
                return i+1;
            }
        }
    }
    if(isEmpty())
    {
        return 0;//Success
    }
    else
    {
        return top->index;
    }
}

int main()
{
    char string[100010];
    int result;
    clear_icanon(0);
    scanf("%[^\n]", string);
    result = checkBrackets(string);
    if(result == 0)
    {
        printf("SUCCESS\n");
    }
    else
    {
        printf("%d\n", result);
    }
    clear_icanon(1);
}