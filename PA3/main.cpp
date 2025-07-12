#include <string>
#include <iostream>

#include "WordString.h"

using namespace std;

int main()
{   
    WordString ws1("Lorem Ipsum is simply        dummy text of the printing and typesetting industry.      Lorem Ipsum has been the industry's         standard dummy text ever since the 1500s, when an unknown printer    took a galley of type and      scrambled it to make a type specimen book. It has survived not only five centuries, but also the                leap into electronic typesetting, remaining essentially          unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing        software like Aldus PageMaker including versions of Lorem Ipsum.");

    cout<<"ws1 number of words: "<<ws1.numberOfWords()<<endl;
    cout<<endl;

    if(ws1.numberOfWords()==91)
        cout<<"NUMBER OF WORDS WS1 TRUE"<<endl;
    else
        cout<<"NUMBER OF WORDS WS1 NOT TRUE"<<endl;
    cout<<endl;

    string string_1 = "     Contrary to popular belief, Lorem Ipsum is not simply random text. It has roots in a piece of classical Latin literature from 45 BC, making it over 2000 years old. Richard       McClintock, a Latin professor at     Hampden-Sydney College in Virginia, looked up one of the more obscure Latin words, consectetur, from a Lorem Ipsum passage, and         going through the cites of the word in classical literature, discovered the undoubtable source. Lorem Ipsum comes from sections 1.10.32 and 1.10.33 of \"de Finibus Bonorum et Malorum\" (The Extremes of Good and Evil) by Cicero, written in 45 BC.       This book is a treatise on the theory of ethics, very popular during the Renaissance. The first line of Lorem Ipsum, \"Lorem ipsum dolor sit amet..\", comes       from a line in section 1.10.32.\n\nThe standard chunk of Lorem Ipsum used since        the 1500s is reproduced below      for those       interested. Sections 1.10.32 and 1.10.33 from \"de Finibus Bonorum et Malorum\" by Cicero are also reproduced in their exact      original form,        accompanied by English versions from the 1914 translation by H. Rackham.";

    cout<<"string_1 number of words: "<<string_1.length()<<endl;
    cout<<endl;

    ws1=ws1 + string_1;
    ws1.strip();
    cout<<ws1<<endl;
    cout<<endl;

    cout<<"ws1 + string_1 number of words: "<<ws1.numberOfWords()<<endl;
    cout<<endl;

    if(ws1.numberOfWords()==267)
        cout<<"NUMBER OF WORDS WS1 + string_1 TRUE"<<endl;
    else
        cout<<"NUMBER OF WORDS WS1 + string_1 NOT TRUE"<<endl;
    cout<<endl;

    string word = ws1.get(201);
    cout<<word<<endl;
    cout<<endl;

    if(word=="Renaissance.")
        cout<<"GET WORDS TRUE"<<endl;
    else
        cout<<"GET WORDS NOT TRUE"<<endl;
    cout<<endl;

    ws1.remove(201);

    word = ws1.get(201);
    cout<<word<<endl;
    cout<<endl;

    if(word=="The")
        cout<<"REMOVE WORDS TRUE"<<endl;
    else
        cout<<"REMOVE WORDS NOT TRUE"<<endl;
    cout<<endl;

    ws1.insertAfter(200,string("transition from the Middle Ages to modernity and was characterized by an effort to revive and surpass the ideas and achievements of classical antiquity -called the Renaissance-."));

    word = ws1.get(227);
    cout<<word<<endl;
    cout<<endl;

    if(word=="Renaissance-.")
        cout<<"insertAfter TRUE"<<endl;
    else
        cout<<"insertAfter NOT TRUE"<<endl;
    cout<<endl;

    WordString ws2, ws3;

    string string_2 = "It is a long       established fact that a reader will be distracted by the readable content of a page when looking at its layout. The         \t\t   point of using Lorem Ipsum is that it has a more-or-less normal distribution of letters, as opposed to using 'Content here, content here',        making it look like readable English. Many desktop publishing        packages and web page editors       \n   now use Lorem Ipsum as their default model text,           and a search for 'lorem ipsum' will uncover many web sites still in their infancy. Various versions have evolved    \n\n    over the years, sometimes by accident, sometimes on          purpose (injected humour and the like).";

    ws2 = ws1 + string_2;

    ws2.strip();
    string catcher = ws2.toString();
    cout<<catcher<<endl;
    cout<<endl;

    if(catcher==ws2.toString())   
        cout<<"toString and == is TRUE"<<endl;
    else
        cout<<"toString and == is NOT TRUE"<<endl;

    ws3 = string_1;

    cout<<"Enter a string to write: "<<endl;
    cin>>ws3;

    int c = ws3.numberOfWords();
    cout<<c<<endl;
    cout<<endl;

    if(ws3=="gebze")
        cout<<"cin>> TRUE"<<endl;
    else
        cout<<"cin>> NOT TRUE"<<endl;
    cout<<endl;

    string new_word = "rinascita(\"rebirth\").";
    ws2.replace(110,new_word);

    cout<<ws2.get(110)<<endl;
    cout<<endl;

    if(ws2.get(110)=="rinascita(\"rebirth\").")
        cout<<"REPLACE TRUE"<<endl;
    else
        cout<<"REPLACE NOT TRUE"<<endl;
    cout<<endl;

    string string_3 = "Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum. Contrary to popular belief, Lorem Ipsum is not simply random text. It has roots in a piece of classical Latin literature from 45 BC, making it over 2000 years old. Richard McClintock, a Latin professor at Hampden-Sydney College in Virginia, looked up one of the more obscure Latin words, consectetur, from a Lorem Ipsum passage, and going through the cites of the word in classical literature, discovered the undoubtable source. Lorem Ipsum comes from sections 1.10.32 and 1.10.33 of \"de Finibus Bonorum et Malorum\" (The Extremes of Good and Evil) by Cicero, written in 45 BC. This book is a treatise on the theory of ethics, very popular during the  transition from the Middle Ages to modernity and was characterized by an effort to revive and surpass the ideas and achievements of classical antiquity -called the Renaissance-. The first line of Lorem Ipsum, \"Lorem ipsum dolor sit amet..\", comes from a line in section 1.10.32.\n\nThe standard chunk of Lorem Ipsum used since the 1500s is reproduced below for those interested. Sections 1.10.32 and 1.10.33 from \"de Finibus Bonorum et Malorum\" by Cicero are also reproduced in their exact original form, accompanied by English versions from the 1914 translation by H. Rackham.";

    WordString ws4(string_3);

    cout<<"ws4 "<<ws4<<endl;
    cout<<"ws1 "<<ws1<<endl;
    ws4.strip();

    if(ws4.toString()==ws1.toString())   
        cout<<"STRIP and == is TRUE"<<endl;
    else
        cout<<"STRIP and == is NOT TRUE"<<endl;
        cout<<endl;

    return 0;
}