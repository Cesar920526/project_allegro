
using namespace std;

class Imagen{

private:
     string text;
     string url;

public:

    Imagen(string u, string t){
        url = u;
        text = t;
    }

    string getUrl(){
        return url;
    }
    void setUrl(string u){
        url = u;
    }

    string getTexto(){
        return text;
    }
    void setTexto(string t){
        text = t;
    }
};
