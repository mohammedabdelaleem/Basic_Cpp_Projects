#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <string>
//#include <bits/stdc++.h>

using namespace std;
void fast()
{
    std::ios_base::sync_with_stdio(0);
    cin.tie(NULL);
}

void connc_strng(string& str1,string& str2)
{
    int i=0,j=0;
    while(i<str1.size() && j<str2.size())
        cout<<str1[i++]<<str2[j++];

    while(i<str1.size())
        cout<<str1[i++];

    while(j<str2.size())
        cout<<str2[j++];
}

void connc_strng2(string& str1,string& str2)
{
    int mx=max(str1.size(),str2.size());

    for(int i=0 ; i<mx ; i++)
    {
        if(i<str1.size())
            cout<<str1[i];

        if(i<str2.size())
            cout<<str2[i];
    }
}

void frequency_letter(string& str)
{
    vector<int>frequency(123);
    for(int i=0 ; i<(int)str.size(); i++)
        frequency[(int)str[i]]++;

    for(int i='A'; i<='Z' ; i++)
        if(frequency[i])cout<<char (i) <<" : "<<frequency[i]<<endl;

    cout<<"\n*******************\n\n";

    for(int i='a'; i<='z' ; i++)
        if(frequency[i])cout<<char (i) <<" : "<<frequency[i]<<endl;

}

void advanced_string_mapping(string &str)
{
    string mapping_small_letters="YZIMNESTODUAPWXHQFBRJKCGVL";
    string mapping_digits="!@#$%^&*()";

    for(int i=0 ; i<(int)str.size(); i++)
    {
        if(str[i]>='a' && str[i]<='z')
            cout<<mapping_small_letters[str[i]-'a'];

        else if(str[i]>='0' && str[i]<='9')
            cout<<mapping_digits[str[i]-'0'];

        else
            cout<<str[i];
    }
}

vector<string> generate_prefixes(string &str)
{
    vector<string> prefixes;
    string prefix = "";
    for (int i = 0; i < str.length(); i++)
    {
        prefix += str[i];
        prefixes.push_back(prefix);
    }
    return prefixes;
}

bool check_if_prefix(vector<string>&prefix_list,string &target)
{
    auto it=find(prefix_list.begin(),prefix_list.end(),target);
    return (it!=prefix_list.end())? true : false;
}

vector<string> generate_sufix(string &str)
{
    vector<string> sufixes;
    string sufix = "";
    for (int i = str.length() - 1; i >=0; i--)
    {
        sufix += str[i];
        sufixes.push_back(sufix);
    }
    return sufixes;
}

bool check_if_sufix(vector<string>&sufix_list,string &target)
{
    auto it=find(sufix_list.begin(),sufix_list.end(),target);
    return (it!=sufix_list.end())? 1 : 0;
}

vector<string> generate_substring(string &str)
{
    vector<string> sub_strings;
    string sub_string = "";

    for (int start = 0; start < str.length(); start++)
    {
        for (int end = start; end < str.length(); end++)
        {
            for (int i = start; i <= end; i++)
            {
                sub_string += str[i];
            }
            sub_strings.push_back(sub_string);
            sub_string.clear();//don't forget string is a class and it has the same vector's functions
        }
    }
    return sub_strings;
}

bool check_if_subString(vector<string>&subString_list,string &target)
{
    auto it=find(subString_list.begin(),subString_list.end(),target);
    return (it!=subString_list.end())? 1 : 0;
}

bool is_sub_sequence(string str1, string str2)  //return if str1 is a subsequence of str2.
{
    int i = 0, j = 0;
    while (i < str1.length() && j < str2.length())
    {
        if (str1[i] == str2[j])
        {
            i++;
        }
        j++;
    }
    return i == str1.length();
    //At the end, if i has reached the length of str1,
    // it means str1 is a subsequence of str2.
}

int string_to_int(string &str)
{
    int num=0;

    //handle negative numbers
    bool negative=false;
    if(str[0]=='-')
    {
        negative=true;
        str.erase(0,1);
    }

    for(int i=0 ; i<str.length(); i++)
    {
        //handle invalid number
        if(str[i]<'0' || str[i]>'9')
            return 0;

        //Add digit to number *************
        num = num*10 + (str[i]-'0');

        // Check for overflow
        if (num > INT_MAX)
            return INT_MAX;
    }
    return negative ? -num : num;
}

int string_to_int_v2(string &str) //with built in functions
{
    //1-
    /*int num;
    stringstream ss(str);
    ss>>num;
    return num;*/

    return stoi(str); // stol , stoul "unsigned long"
}

string grouping(string& str)
{
    string group="";
    char space=' ';
    for(int i=0 ; i<str.length(); i++)
    {
        if(str[i]==str[i+1])
            group.push_back(str[i]);
        else
        {
            group.push_back(str[i]);
            group.push_back(space);
        }//الحمد لله
    }
    return group;
}

void compression(string& str)
{
    char under_score='_',current_char='a';
    int ctr=0;
    for(int i=0 ; i<str.size(); i++)
    {
        current_char=str[i];
        if(str[i]==str[i+1])ctr++;
        else
        {
            ctr++;
            cout<<current_char<<ctr;
            if(i!=str.length()-1)cout<<under_score;
            ctr=0;
        }
    }
}

void compare(string& str1,string& str2) //yes?s1<=s1
{
    int len1=str1.length();
    int len2=str2.length();

    for(int i=0; i<len1 && i<len2 ; i++)
    {
        if(str1[i] < str2[i])
        {
            cout<<"YES";
            return;
        }
        else if(str1[i] > str2[i])
        {
            cout<<"NO";
            return;
        }
    }
    (len1<=len2)?cout<<"yes":cout<<"no";//الحمد لله
}

int number_of_digits(int num)
{
    int c;
    while(num)
    {
        c++;
        num/=10;
    }
    return c;
}

//at least 6 char_digit and we will add 5555
void add_5555(string str)
{
    bool done=false;
    int x=0;
    char left_string_digit;
    int len=str.length();
    int last_4characters=len-4;
    int num=0;
    string addition="";
    for(int i =last_4characters ; i<len ; i++)
        num = num*10 + (str[i]-'0');

    str.erase(last_4characters,4);
    num+=5555;
    if(number_of_digits(num)<=4)
    {
        string addition=to_string(num);
        str+=addition;
    }
    else
    {
        addition=to_string(num);
        left_string_digit=addition[0];
        addition.erase(0,1);
        for(int i=str.length()-1; i>=0 ; i--)
        {
            if(str[i]!='9')
            {
                x=str[i]-'0';
                x+=(left_string_digit-'0');
                str[i]=x+'0';
                str+=addition;
                done=true;
                break;
            }
        }
    }

    if(done==false)
    {
        str.insert(str.begin(),'1');
        str+=addition;
    }
    cout<<str<<endl;
}//i think there is not an optimal solution , but yah [الحمد لله ].
//all examples in video are ok الحمد لله

bool is_sub_string_v2(const string& base, const string& target1, const string& target2)
{
    return base.find(target1) != string::npos || base.find(target2) != string::npos;
}

int search_for_operation(string op) //time : O(1) , space : O(1)
{
    if(op == "pop_back")
        return 1;

    else if(op == "front")
        return 2;

    else if(op == "back")
        return 3;

    else if(op == "sort")
        return 4;

    else if(op == "reverse")
        return 5;

    else if(op == "print")
        return 6;

    else if(op == "substr")
        return 7;

    else if(op == "push_back")
        return 8;

    // Add a default case to handle unknown operations
    else
        return 0;
}

void black_box(string &str,int operation)//O(nlogn) - O(n^2)
{
    char x;
    int start,_end,pos;

    switch(operation)
    {
    case 1:
        if(str.length() > 0)
            str.pop_back();
        break;

    case 2:
        if(str.length() > 0)
            cout<<str.front()<<endl;
        break;

    case 3:
        if(str.length() > 0)
            cout<<str.back()<<endl;
        break;

    case 4:
        cin>>start>>_end;
        if(start>_end)swap(start,_end);
        sort(str.begin()+(start-1),str.begin()+_end);//O(nlogn) - O(n^2)*****
        break;

    case 5:
        cin>>start>>_end;
        if(start>_end)swap(start,_end);
        reverse(str.begin()+(start-1),str.begin()+_end); //O(n)
        break;

    case 6:
        cin>>pos;
        if(!(pos-1 < 0 || pos-1 >= str.length()))
            cout<<str[pos]<<endl;
        break;

    case 7:
        cin>>start>>_end;
        if(start>_end)swap(start,_end);
        cout<<str.substr(start-1,_end)<<endl; //O(n)
        break;

    case 8:
        cin>>x;
        str.push_back(x);
        break;

    default:
        // Handle unknown operations
        cout<<"Unknown operation"<<endl;
        break;
    }
}

int MaxSubsequence(string arr)
{
    int  c=0;
    for(int i=0; i<arr.length()-1; i++)
    {
        if(arr[i]==arr[i+1])
            c--;
    }
    return arr.length()+c;
}

string sort_string(string &str)//using insertion sort ==> Memory limit exceeded on test 3
{
    for(int step=1 ; step<str.size() ; step++)
    {
        int key=str[step];
        int j=step-1;

        while(j>=0 && key<str[j])
        {
            str[j+1]=str[j];
            j--;
        }
        str[j+1]=key;
    }
    return str;
}

void sort_string_v2(string &str)
{
    vector<int>freq(123);

    for(int i=0 ; i<str.size(); i++)
        freq[(int)str[i]]++;

    int idx=0;
    for(int i=97; i<=122 ; i++)
        for(int j=0 ; j<freq[i]; j++)
            str[idx++]=char(i);
}

void sort_string_v3()
{
    int size;
    cin>>size;

    vector<int>freq(123);

    for(int i=0 ; i<size ; i++)
    {
        char c;
        cin>>c;
        freq[(int)c]++;
    }
    for(int i=97 ; i<=122 ; i++ )
    {
        if(freq[i])while(freq[i]--)cout<<char(i);
    }
}

int count_words(string &str)
{
    int count=0; //to count the number of words in the input string
    bool in_word=false;  //flag to keep track if the currently character is already inside the word

    for(char ch : str)
    {
        if(isalpha(ch))
        {
            if(!in_word)
            {
                in_word=true;
                count++;
            }
        }
        else
        {
            in_word=false;
        }
    }
    return count;
}

void sstream_examples()
{
     //1-
    string my_string;
    float price=0.0;
    int quantity=0;

    cout<<"Enter the price : ";
    getline(cin,my_string);
    stringstream(my_string)>>price;

    cout<<"Enter the Quantity : ";
    getline(cin,my_string);
    stringstream(my_string)>>quantity;

    cout<<"total price = "<<quantity * price;

//2-
    string s = "Hello, world!";
    stringstream ss(s); // Create a stringstream object with s as input

    string word;
    while (ss >> word)   // Read each word from the stringstream
    {
        cout << word << endl; // Output each word on a new line
    }
//3-
    stringstream ss2; // Create a new stringstream object
    ss2 << "I" << " " << "love" << " " << "programming"; // Write multiple tokens to the stringstream
    string output = ss2.str(); // Get the concatenated string from the stringstream
    cout << output << endl; // Output the concatenated string

    //4-
 string s2 = "42";
    stringstream ss3(s2); // Create a stringstream object with s as input

    int num;
    ss3 >> num; // Read the integer from the stringstream

    cout << num << endl; // Output the integer
}

void reverse_words(string& str)
{
    stringstream ss(str);

    char space=' ';
    string word="";
    string reversed="";
    while(ss>>word)
    {
        reverse(word.begin(),word.end());
        reversed+=(word+space);
    }
    reversed.pop_back(); //to remove the space
    cout<<reversed;
}

void reverse_words_v2(string& str) //more efficient
{
    istringstream iss(str); // Create an input string stream object

    string word;
    string reversed = ""; // Initialize the reversed string to an empty string

    while (iss >> word) { // Loop through each word in the input string
        for (int i = word.length() - 1; i >= 0; i--) { // Loop through each character in the word, backwards
            reversed += word[i]; // Add the character to the reversed string
        }
        reversed += " "; // Add a space after each word
    }

    reversed.pop_back(); // Remove the extra space at the end

    cout << reversed << endl; //
}

void replace_word(string &str,string &substr)
{
    size_t pos=0;
    do
    {
        pos = str.find(substr);
        if(pos != string::npos)
            str.replace(pos, substr.length()," ");
    }
    while(pos!=string::npos);

    cout<<str<<endl;
}


void to_lower(string &str)//1-
{
    for(int i=0 ; i<str.length() ; i++)
    {
        int ch=str[i];
        if(isupper(ch))
            str[i]=tolower(ch);
    }
}

void delete_all_letters_not_EGYPT(string &str)
{
    for(int i = str.length() - 1; i >= 0; i--)
    {
        if(str[i] != 'e' && str[i] != 'g' && str[i] != 'y' && str[i] != 'p' && str[i] != 't')
            str.erase(i, 1);
    }
}

int egypt_number(string &str) // count Egypt
{
//e=1 , g=2 , y=3 ,p=4 , t=5

    //get sum
    int sum=0;
    for(int i=0 ; i<str.length() ; i++)
    {
        if(str[i]=='e' || str[i]=='E')
            sum+=1;

        else if(str[i]=='g' || str[i]=='G')
            sum+=2;

        else if(str[i]=='y' || str[i]=='Y')
            sum+=3;

        else if(str[i]=='p' || str[i]=='P')
            sum+=4;

        else if(str[i]=='t' || str[i]=='T')
            sum+=5;
    }
    //count egypt
    return sum/15;
}

//we can handle it by map structure
//http://www.cleartrip.com/signin/service?username=test&pwd=test&profile=developer&role=ELITE&key=manager
void URL(string str)
{
    string substr1="username";
    string substr2="pwd";
    string substr3="profile";
    string substr4="role";
    string substr5="key";

    string val1="";
    string val2="";
    string val3="";
    string val4="";
    string val5="";

    size_t pos=str.find(substr1);
    int i=pos+substr1.size()+1; //+1 ==> =
    while(str[i]!='&' && i<str.length())
    {
        val1+=str[i++];
    }

      size_t pos2=str.find(substr2);
     i=pos2+substr2.size()+1; //+1 ==> =
    while(str[i]!='&' && i<str.length())
    {
        val2+=str[i++];
    }

     size_t pos3=str.find(substr3);
     i=pos3+substr3.size()+1; //+1 ==> =
    while(str[i]!='&' && i<str.length())
    {
        val3+=str[i++];
    }

      size_t pos4=str.find(substr4);
     i=pos4+substr4.size()+1; //+1 ==> =
    while(str[i]!='&' && i<str.length())
    {
        val4+=str[i++];
    }

      size_t pos5=str.find(substr5);
     i=pos5+substr5.size()+1; //+1 ==> =
    while(str[i]!='&' && i<str.length())
    {
        val5+=str[i++];
    }

    cout<<substr1<<": "<<val1<<endl;
    cout<<substr2<<": "<<val2<<endl;
    cout<<substr3<<": "<<val3<<endl;
    cout<<substr4<<": "<<val4<<endl;
    cout<<substr5<<": "<<val5<<endl;
}

/////////////////////////////////////////
void insert_v2d(vector<vector<string>>& v2d)
{
    for(int i = 0; i < v2d.size(); i++)
    {
        for(int j = 0; j < v2d[i].size(); j++)
        {
            cin >> v2d[i][j];
        }
    }
}

void print_v2d(const vector<vector<string>>& v2d)
{
    for(int i = 0; i < v2d.size(); i++)
    {
        for(int j = 0; j < v2d[i].size(); j++)
        {
            cout << v2d[i][j] << " ";
        }
        cout << endl;
    }
}
/*
at main :
int rows=3,cols=4;
vector<vector<string>>v2d(rows,vector<string>(cols));
insert_v2d(v2d);
print_v2d(v2d);
*/

void max_spilt(string &str)
{
    string substr;
    int L_c=0,R_c=0,count=0;

    for(int i=0 ; i<str.length()+1 ; i++)
    {
        if(L_c == R_c && L_c!=0) // i<str.length()+1  ==> +1 to enter and check the condition
          {
            L_c=0;R_c=0;
            substr.push_back('\n');
            count++;
        }
        if(str[i]=='L')
        {
            substr.push_back('L');
            L_c++;
        }
         else if(str[i]=='R')
        {
            substr.push_back('R');
            R_c++;
        }
    }
    cout<<count<<endl;
    cout<<substr;
}

int main()
{
string str;
cin>>str;
max_spilt(str);
    return 0;
}

