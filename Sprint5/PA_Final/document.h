#ifndef DOCUMENT_H
#define DOCUMENT_H
#include <string>
/*William Dunn
 * this is a class that will hold all data relavent to a document that is tied to a term
 * will be stored in term and hold how many time that term appears in a given term
 */
using namespace std;
class document
{
public:
    float tf;
    string doc;
    document();
    document(string, float);
    document(const document&);
    //bool operator<()
    const document& operator-(const document&);
    bool operator<( document&)const;
    bool operator>( document&)const;
    bool operator<( const document&)const;
    bool operator>( const document&)const;
    //bool operator<( Term&);
    bool operator==(const document&);
     bool operator==( document&);
     string tostring();
     friend std::ostream& operator<<(std::ostream&, const document&);
    const document& operator=(const document&);
};

#endif // DOCUMENT_H
