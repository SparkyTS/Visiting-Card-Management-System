#include<iostream>
#include<fstream>
#include<string.h>
#include<iomanip>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
using namespace std;

/*-------V-card-----------
| Name :                 |
| position :             |
| contact_no:            |
| Company_name :         |
| Compnay_web :          |
| Company_email :        |
------------------------*/
int find_substr(char *a,char *b)
{
int j;char x,c[20];
    for(int i=0;i<strlen(a);i++)
    {
        if(b[0]==a[i])
        {
            for(j=0;j<strlen(b);j++)
                c[j]=a[i+j];

                c[j]='\0';

            if(!strcmp(c,b))
            {
                cout<<"\nDid you mean "<<a<<" ?  y/n : ";
                cin>>x;
                if(x=='n')
                    return 0;
                return 1;
            }
        }

        else if(i==strlen(a)-1)
            return 0;
    }
}

void TOUPPER(char *y)
{
 for(int i=0;y[i]!=NULL;i++)
        y[i]=toupper(y[i]);
}

static int i;

class Vcard
{
    char name[30];
    char position[30];
    long long contact_no;
    char C_name[20];
    char C_web[40];
    char C_email[50];
public:
    void getVcard()
    {
      cout<<"Enter Name : ";
      cin.ignore();
      cin.getline(name,29); TOUPPER(name);cin.ignore();
      cout<<"Enter Position : ";
      cin.getline(position,29); TOUPPER(position);cin.ignore();
      cout<<"Enter Contact No. : ";
      cin>>contact_no;
      cout<<"\nEnter Company Name : ";
      cin.ignore();
      cin.getline(C_name,19); TOUPPER(C_name);
      cout<<"\nEnter Company Website : ";
      cin.getline(C_web,39);
      cout<<"\nEnter Company Email : ";
      cin.getline(C_email,49);
      cin.ignore();
    }
    void showVcard()
    {   cout.setf(ios::left,ios::adjustfield);
        cout<<"\n\n------------------------------------------------\n"
            <<"|           Name : "<<setw(28)<<name<<"|"<<endl
            <<"|       Position : "<<setw(28)<<position<<"|"<<endl
            <<"|    Contact No. : "<<setw(28)<<contact_no<<"|"<<endl
            <<"|   Company Name : "<<setw(28)<<C_name<<"|"<<endl
            <<"|Company Website : "<<setw(28)<<C_web<<"|"<<endl
            <<"|  Company Email : "<<setw(28)<<C_email<<"|"<<endl
            <<"------------------------------------------------";
    }
void displaydata()
    {
        if(i==0)
           cout<<"*-*-*-*-Available Visiting Cards -*-*-*-*"
            <<"\n\nName                       Contact No                    Company Name                  Position             Company E-mail                     Company Website\n",i++;

        cout<<"\n\n";cout.setf(ios::left,ios::adjustfield);
        cout<<setw(27)<<name<<setw(30)<<contact_no<<setw(30)<<C_name<<setw(21)<<position<<setw(35)<<C_email<<setw(33)<<C_web<<"\n";
        for(int j=0;j<45;j++) cout<<"----";
    }
    int storeVcard();
    int showallVcards();
    int findVcard();
    int deleteVcard();
    int updateVcard();
};
int Vcard::storeVcard()
{
    ofstream fout;
    getVcard();
    fout.open("vcard.dat",ios::app|ios::binary);
    fout.write((char*)this,sizeof(*this));
    fout.close();
    return 0;
}
Vcard::showallVcards()
{
    ifstream fin;int choise;i=0;
    fin.open("vcard.dat",ios::in|ios::binary);
    if(!fin)
    {
        cout<<"\nFile is Empty...!";
        return 0;
    }
    fin.read((char*)this,sizeof(*this));
    cout<<"Select View :\n1.LIST VIEW\n2.CARD VIEW\n\nInput : ";
    cin>>choise;
    cout<<"\n\n";
    switch(choise)
    {
        case 2:
            while(!fin.eof())
            {
            showVcard();
            fin.read((char*)this,sizeof(*this));
            }break;
        default:
            while(!fin.eof())
            {
            displaydata();
            fin.read((char*)this,sizeof(*this));
            }break;
    }
    fin.close();
}
int Vcard::findVcard()
{
    ifstream fin;
    int flag=0;
    fin.open("vcard.dat",ios::in|ios::binary);
    if(!fin)
    {
        cout<<"\nFile is Empty...!";
        return 0;
    }
    int choice;
    cin.ignore();
    cout<<"Select option to Search By\n1.Name\n2.Contact No.\n3.Company Name\n\ninput : ";
    cin>>choice;
    switch(choice)
    {
    case 1:
        char n[30];
        cout<<"Enter Name of person to find card : ";
        cin.ignore();
        cin.getline(n,29);TOUPPER(n);
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof())
        {
            if(!strcmp(n,name) || find_substr(name,n))
            {
                cout<<"\n*-*-*-*- Visiting Card Found -*-*-*-*\n";
                showVcard();
                flag=1;
            }
            fin.read((char*)this,sizeof(*this));
        }
        if(flag==0)
            cout<<"\nVisiting card of "<<n<<" is not available in File.";
        fin.close();
        break;

    case 2:
        long long ph;
        cout<<"\nEnter Contact No. of person to find card : ";
        cin.ignore();
        cin>>ph;
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof())
        {
            if(ph==contact_no)
            {
                cout<<"\n*-*-*-*- Visiting Card Found -*-*-*-*\n";
                showVcard();
                flag=1;
            }
            fin.read((char*)this,sizeof(*this));
        }
        if(flag==0)
            cout<<"\nVisiting card of contact no "<<ph<<" is not available in File.";
        fin.close();
        break;

//    case 3:
//        char c[30];
//        cout<<"Enter Company Name of person to find card : ";
//        cin.ignore();
//        cin.getline(c,29);TOUPPER(c);
//        fin.read((char*)this,sizeof(*this));
//        while(!fin.eof())
//        {
//            if(!strcmp(c,C_name) || find_substr(C_name,c))
//            {
//                cout<<"\n*-*-*-*- Visiting Card Found -*-*-*-*\n";
//                showVcard();
//                flag=1;break;
//            }
//            fin.read((char*)this,sizeof(*this));
//        }
//        if(flag==0)
//            cout<<"\nVisiting card with company name : "<<c<<" is not available in File.";
//        fin.close();
//        break;
//
        case 3:
        char c[30];
        cout<<"Enter Company Name of person to find card : ";
        cin.ignore();
        cin.getline(c,29);TOUPPER(c);
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof())
        {
            if(!strcmp(c,C_name) || find_substr(C_name,c))
            {
                cout<<"\n*-*-*-*- Visiting Card Found -*-*-*-*\n";
                showVcard();
                flag=1;
                break;
            }
            fin.read((char*)this,sizeof(*this));
        }
        if(flag==0)
            cout<<"\nVisiting card with Companay Name "<<c<<" is not available in File.";
        fin.close();
        break;

    default :
        cout<<"\n<<<<INVALID CHOISE>>>>";
    }
}
Vcard::deleteVcard()
{
    ifstream fin;
    int flag1=0,flag2=0;
    fin.open("vcard.dat",ios::in|ios::binary);
    if(!fin)
    {
        cout<<"\nFile is Empty...!";
        return 0;
    }
    char n[30];
    cin.ignore();
    cout<<"\nEnter Name of person to delete card : ";
    cin.getline(n,29);TOUPPER(n);
    ofstream fout;
    fout.open("temp.dat",ios::app|ios::binary);
    fin.read((char*)this,sizeof(*this));
    while(!fin.eof())
    {
        if(strcmp(n,name) && !find_substr(name,n))
            fout.write((char*)this,sizeof(*this)),flag1++;
        fin.read((char*)this,sizeof(*this)),flag2++;
    }
    fin.close();
    fout.close();
    remove("vcard.dat");
    rename("temp.dat","vcard.dat");
    if(flag1==flag2)
    cout<<"\n\nNo Visiting Card Found to Delete with name "<<n;
    else
        cout<<"\n\nVisiting Card of "<<n<<" is Deleted.";

}
int Vcard::updateVcard()
{
    fstream file;int choise,flag=0;Vcard temp;
    file.open("vcard.dat",ios::in|ios::out|ios::ate|ios::binary);
    if(!file)
    {
        cout<<"\nFile not Found...!";
        return 0;
    }
    file.seekg(0);
    char n[30];
    cout<<"Enter Name of person to Update visiting card : ";
    cin.ignore();
    cin.getline(n,29);TOUPPER(n);
    file.read((char*)this,sizeof(*this));
    while(!file.eof())
    {
        if(!strcmp(n,name) || find_substr(name,n))
        {
            flag=1;
            cout<<"\n*-*-*-*- Visiting Card -*-*-*-*\n";showVcard();
            cout<<"\n\nWhat You Want To Update ?\n"
                <<"1.Name\n"
                <<"2.Position\n"
                <<"3.Contact No.\n"
                <<"4.Company Name\n"
                <<"5.Company Website\n"
                <<"6.Company Email\n"
                <<"7.Everything\n"
                <<"Any Other key to exit\n\nInput : ";
            cin>>choise;
            switch(choise)
            {
                case 1:
                    temp=*this;
                    cin.ignore();
                    cout<<"\nEnter Name : ";
                    cin.getline(temp.name,29);TOUPPER(temp.name);
                    file.seekp(file.tellp()-sizeof(*this));
                    file.write((char*)&temp,sizeof(temp));
                    break;
                case 2:
                    temp=*this;
                    cin.ignore();
                    cout<<"\nEnter "<<n<<"'s NEW Position : ";
                    cin.getline(temp.position,29);TOUPPER(temp.position);
                    file.seekp(file.tellp()-sizeof(*this));
                    file.write((char*)&temp,sizeof(temp));
                    break;
                case 3:
                    temp=*this;
                    cin.ignore();
                    cout<<"\nEnter "<<n<<"'s NEW Contact No : ";
                    cin>>temp.contact_no;
                    file.seekp(file.tellp()-sizeof(*this));
                    file.write((char*)&temp,sizeof(temp));
                    break;
                case 4:
                    temp=*this;
                    cin.ignore();
                    cout<<"\nEnter "<<n<<"'s New Company Name : ";
                    cin.getline(temp.C_name,19);TOUPPER(temp.C_name);
                    file.seekp(file.tellp()-sizeof(*this));
                    file.write((char*)&temp,sizeof(temp));
                    break;
                case 5:
                    temp=*this;
                    cin.ignore();
                    cout<<"\nEnter "<<n<<"'s NEW Company Website : ";
                    cin.getline(temp.C_web,39);
                    file.seekp(file.tellp()-sizeof(*this));
                    file.write((char*)&temp,sizeof(temp));
                    break;
                case 6:
                    temp=*this;
                    cin.ignore();
                    cout<<"\nEnter "<<n<<"'s NEW Company E-mail id : ";
                    cin.getline(temp.C_email,49);
                    file.seekp(file.tellp()-sizeof(*this));
                    file.write((char*)&temp,sizeof(temp));
                    break;
                 case 7:
                    file.seekp(file.tellp()-sizeof(*this));
                    getVcard();
                    file.write((char*)this,sizeof(*this));
                    break;
                 default:
                    file.close();
                    cout<<"\n<<<<<<INVALID CHOICE>>>>>>";
                    getch();
                    return 0;
                    break;
            }
        }
        file.read((char*)this,sizeof(*this));
    }
    file.close();
    if(flag==0)
        cout<<"\nNo Visiting Card Found To Update With Name : "<<n;
    else
        cout<<"\n\nVisiting Card of "<<n<<" is Updated Successfully...!\n";

    return 1;
}
int menu()
{
    cout<<"*-*-*-*- Visiting Card Management System -*-*-*-*\n\n"
        <<"1.Add New Visiting Card"<<endl
        <<"2.Show All Visiting Card"<<endl
        <<"3.Find Visiting Card"<<endl
        <<"4.Update Visiting Card"<<endl
        <<"5.Delete Visiting Card"<<endl
        <<"Any Other key to exit...\n\nInput : ";
        int choice;
        cin>>choice;
        cout<<"\n";
        return choice;
}

main()
{
    Vcard v;
    while(1)
    {
        system("cls");
        switch(menu())
        {
            case 1: v.storeVcard();break;
            case 2: i=0;v.showallVcards();getch(); break;
            case 3: v.findVcard();getch();     break;
            case 4: v.updateVcard();getch();   break;
            case 5: v.deleteVcard();getch();   break;
            default: {cout<<"\n\n-*-*-* Developed by Tanay Shah -*-*-*";getch();exit(0);}
        }
    }
}
