#include <concepts>
#include <ostream>
#include <iostream>

template<typename I> requires std::integral<I>
class rational
{
I num_;
I den_;

I mcd(I a, I b) const { //metto const perchè num_ e den_ non vengono modificati 
    a = std::abs(a);
    b = std::abs(b);
    while (b != 0) {
        I resto = a % b;
        a = b;
        b = resto;
    }
    return a;
}

I mcm(I a, I b) const {
    if (a == 0 || b == 0) return 0; //if a or b ==0
    I MCD = mcd(a, b);
    return std::abs(a * b) / MCD;
}

void simplify() { //non metto const perchè num_ e den_ vengono modificati
    I MCD = mcd(num_, den_);
    num_ /= MCD;
    den_ /= MCD;
}


public:

/* DEFAULT CONSTRUCTOR */ 
    rational()
        : num_(I{3}), den_(I{2}) //inizializzo a 2 i valori di num e den
    {} // Non gestisco i casi problematici 

/* USER-DEFINED CONSTRUCTOR */
    rational(const I& pnum, const I& pden)
        : num_(pnum), den_(pden)
    { 
    // Standardizzo tutti i casi problematici in modo da gestirli con semplicità direttamente nelle operazioni
        if (den_ == 0) {
            if (num_ > 0) num_ = 1; // 1/0 -> Inf
            else if (num_ < 0) num_ = -1; // -1/0 -> -Inf
            else num_ == 0; // 0/0 -> NaN
            return;
        }

        else if (den_ > 0) {
            if (num_ == 0) den_ = 1; // 0/1 -> 0
            return;
        }
    
    // Gestisco l'eventuale segno negativo del denominatore spostandolo a numeratore
        else if (den_ < 0) {
            num_=-num_;
            den_=-den_;
        }
    
    // Semplifico la frazione già nel constructor
        simplify();
    }


 /* METHODS NUM & DEN */
    I num() const { return num_; }
    I den() const { return den_; }


/* CANONICAL IMPLEMENTATION OF += */
    rational& operator+=(const rational& other) {  //prende un const reference e restituisce un reference (che viene recuperata con il dereference *)
        
        if ((num_ == 0 && den_ == 0) || (other.num_ == 0 && other.den_ == 0)) {num_ = 0 ; den_ = 0 ; return *this;} // Gestione NaN
        
        if ((num_ == 1 && den_ == 0) && (other.num_ == 1 && other.den_ == 0)) {num_ = 1 ; den_ = 0 ; return *this;} //Inf+Inf=Inf
        if ((num_ == -1 && den_ == 0) && (other.num_ == -1 && other.den_ == 0)) {num_ = -1 ; den_ = 0 ; return *this;} //-Inf-Inf=-Inf
        if ((num_ == 1 && den_ == 0) && (other.num_ == -1 && other.den_ == 0)) {num_ = 0 ; den_ = 0 ; return *this;} //Inf-Inf=NaN
        if ((num_ == -1 && den_ == 0) && (other.num_ == 1 && other.den_ == 0)) {num_ = 0 ; den_ = 0 ; return *this;} //-Inf+Inf=NaN

        if ((num_ == 1 && den_ == 0) && (other.den_ != 0)) {num_ = 1 ; den_ = 0 ; return *this;} //Inf+a=Inf
        if ((num_ == -1 && den_ == 0) && (other.den_ != 0)) {num_ = -1 ; den_ = 0 ; return *this;} //-Inf+a=-Inf
        if ((den_ != 0) && (other.num_ == 1 && other.den_ == 0)) {num_ = 1 ; den_ = 0 ; return *this;} //a+Inf=Inf
        if ((den_ != 0) && (other.num_ == -1 && other.den_ == 0)) {num_ = -1 ; den_ = 0 ; return *this;} //a-Inf=-Inf

        I MCM = mcm(den_ , other.den_) ;
        num_ = num_ * MCM / den_ + other.num_ * MCM / other.den_ ;
        den_ = MCM ;
        simplify();

        return *this;
    }
/* CANONICAL IMPLEMENTATION OF + */
//il valore della somma viene salvato in una variabile nuova a parte
//a differenza della somma, il valore dell'incremento viene salvato direttamente in a

    rational operator+(const rational& other) const { //prende un const reference, restituisce per valore ed é dichiarato const

        rational rat = *this ; //inizializzo un NUOVO oggetto di tipo rational
        rat = rat.operator+=(other);
        //la semplificazione viene già svolta in operator+= !!

        return rat; 
    }


/* CANONICAL IMPLEMENTATION OF -= */
    rational& operator-=(const rational& other) { 

        if ((num_ == 0 && den_ == 0) || (other.num_ == 0 && other.den_ == 0)) {num_ = 0 ; den_ = 0 ; return *this;} // Gestione NaN

        if ((num_ == 1 && den_ == 0) && (other.num_ == -1 && other.den_ == 0)) {num_ = 1 ; den_ = 0 ; return *this;} //Inf+Inf=Inf
        if ((num_ == -1 && den_ == 0) && (other.num_ == 1 && other.den_ == 0)) {num_ = -1 ; den_ = 0 ; return *this;} //-Inf-Inf=-Inf
        if ((num_ == 1 && den_ == 0) && (other.num_ == 1 && other.den_ == 0)) {num_ = 0 ; den_ = 0 ; return *this;} //Inf-Inf=NaN
        if ((num_ == -1 && den_ == 0) && (other.num_ == -1 && other.den_ == 0)) {num_ = 0 ; den_ = 0 ; return *this;} //-Inf+Inf=NaN

        if ((num_ == 1 && den_ == 0) && (other.den_ != 0)) {num_ = 1 ; den_ = 0 ; return *this;} //Inf-a=Inf
        if ((num_ == -1 && den_ == 0) && (other.den_ != 0)) {num_ = -1 ; den_ = 0 ; return *this;} //-Inf-a=-Inf
        if ((den_ != 0) && (other.num_ == 1 && other.den_ == 0)) {num_ = -1 ; den_ = 0 ; return *this;} //a-Inf=-Inf
        if ((den_ != 0) && (other.num_ == -1 && other.den_ == 0)) {num_ = 1 ; den_ = 0 ; return *this;} //a+Inf=Inf

        I MCM = mcm(den_ , other.den_) ;
        num_ = num_ * MCM / den_ - other.num_ * MCM / other.den_ ;
        den_ = MCM ;
        simplify();

        return *this; 
    }
/* CANONICAL IMPLEMENTATION OF - */
    rational operator-(const rational& other) const {

        rational rat = *this ;
        rat = rat.operator-=(other);

        return rat;
    }


/* CANONICAL IMPLEMENTATION OF *= */
    rational& operator*=(const rational& other) {

        if ((num_ == 0 && den_ == 0) || (other.num_ == 0 && other.den_ == 0)) {num_ = 0 ; den_ = 0 ; return *this;} // Gestione NaN

        if ((num_ == 1 && den_ == 0) && (other.num_ == 1 && other.den_ == 0)) {num_ = 1 ; den_ = 0 ; return *this;} //Inf*Inf=Inf
        if ((num_ == -1 && den_ == 0) && (other.num_ == -1 && other.den_ == 0)) {num_ = 1 ; den_ = 0 ; return *this;} //-Inf*-Inf=Inf
        if ((num_ == 1 && den_ == 0) && (other.num_ == -1 && other.den_ == 0)) {num_ = -1 ; den_ = 0 ; return *this;} //Inf*-Inf=-Inf
        if ((num_ == -1 && den_ == 0) && (other.num_ == 1 && other.den_ == 0)) {num_ = -1 ; den_ = 0 ; return *this;} //-Inf*Inf=-Inf

        if ((num_ == 1 && den_ == 0) && (other.num_ == 0 && other.den_ == 1)) {num_ = 0 ; den_ = 0 ; return *this;} //Inf*0=NaN
        if ((num_ == -1 && den_ == 0) && (other.num_ == 0 && other.den_ == 1)) {num_ = 0 ; den_ = 0 ; return *this;} //-Inf*0=NaN
        if ((num_ == 0 && den_ == 1) && (other.num_ == 1 && other.den_ == 0)) {num_ = 0 ; den_ = 0 ; return *this;} //0*Inf=NaN
        if ((num_ == 0 && den_ == 1) && (other.num_ == -1 && other.den_ == 0)) {num_ = 0 ; den_ = 0 ; return *this;} //0*-Inf=NaN

        if ((num_ == 1 && den_ == 0) && (other.num_ > 0 && other.den_ != 0 )) {num_ = 1 ; den_ = 0 ; return *this;} //Inf*a=Inf, a>0
        if ((num_ == -1 && den_ == 0) && (other.num_ > 0 && other.den_ != 0)) {num_ = -1 ; den_ = 0 ; return *this;} //-Inf*a=-Inf
        if ((num_ > 0 && den_ != 0) && (other.num_ == 1 && other.den_ == 0)) {num_ = 1 ; den_ = 0 ; return *this;} //a*Inf=Inf
        if ((num_ > 0 && den_ != 0) && (other.num_ == -1 && other.den_ == 0)) {num_ = -1 ; den_ = 0 ; return *this;} //a*-Inf=-Inf

        if ((num_ == 1 && den_ == 0) && (other.num_ < 0 && other.den_ != 0 )) {num_ = -1 ; den_ = 0 ; return *this;} //Inf*a=-Inf, a<0
        if ((num_ == -1 && den_ == 0) && (other.num_ < 0 && other.den_ != 0)) {num_ = 1 ; den_ = 0 ; return *this;} //-Inf*a=Inf
        if ((num_ < 0 && den_ != 0) && (other.num_ == 1 && other.den_ == 0)) {num_ = -1 ; den_ = 0 ; return *this;} //a*Inf=-Inf
        if ((num_ < 0 && den_ != 0) && (other.num_ == -1 && other.den_ == 0)) {num_ = 1 ; den_ = 0 ; return *this;} //a*-Inf=Inf

        num_ = num_ * other.num_ ;
        den_ = den_ * other.den_ ;
        simplify();

        return *this; 
    }
/* CANONICAL IMPLEMENTATION OF *  */
    rational operator*(const rational& other) const {

        rational rat = *this;
        rat = rat.operator*=(other);
        
        return rat;
    }


/* CANONICAL IMPLEMENTATION OF /= */
    rational& operator/=(const rational& other) {

        if ((num_ == 0 && den_ == 0) || (other.num_ == 0 && other.den_ == 0)) {num_ = 0 ; den_ = 0 ; return *this;} // Gestione NaN

        if ((num_ == 1 && den_ == 0) && (other.num_ == 1 && other.den_ == 0)) {num_ = 0 ; den_ = 0 ; return *this;} // Inf/Inf=NaN
        if ((num_ == -1 && den_ == 0) && (other.num_ == -1 && other.den_ == 0)) {num_ = 0 ; den_ = 0 ; return *this;} // -Inf/-Inf=NaN
        if ((num_ == 1 && den_ == 0) && (other.num_ == -1 && other.den_ == 0)) {num_ = 0 ; den_ = 0 ; return *this;} // Inf/-Inf=NaN
        if ((num_ == -1 && den_ == 0) && (other.num_ == 1 && other.den_ == 0)) {num_ = 0 ; den_ = 0 ; return *this;} // -Inf/Inf=NaN

        if ((num_ == 1 && den_ == 0) && (other.num_ == 0 && other.den_ == 1)) {num_ = 1 ; den_ = 0 ; return *this;} // Inf/0=Inf
        if ((num_ == -1 && den_ == 0) && (other.num_ == 0 && other.den_ == 1)) {num_ = -1 ; den_ = 0 ; return *this;} // -Inf/0=-Inf
        if ((num_ == 0 && den_ == 1) && (other.num_ == 1 && other.den_ == 0)) {num_ = 0 ; den_ = 1 ; return *this;} // 0/Inf=0
        if ((num_ == 0 && den_ == 1) && (other.num_ == -1 && other.den_ == 0)) {num_ = 0 ; den_ = 1 ; return *this;} // 0*/Inf=0

        if ((num_ == 1 && den_ == 0) && (other.num_ > 0 && other.den_ != 0 )) {num_ = 1 ; den_ = 0 ; return *this;} // Inf/a=Inf, a>0
        if ((num_ == -1 && den_ == 0) && (other.num_ > 0 && other.den_ != 0)) {num_ = -1 ; den_ = 0 ; return *this;} // -Inf/a=-Inf

        if ((num_ != 0 && den_ != 0) && (other.num_ == 1 && other.den_ == 0)) {num_ = 0 ; den_ = 1 ; return *this;} // a/Inf=0
        if ((num_ != 0 && den_ != 0) && (other.num_ == -1 && other.den_ == 0)) {num_ = 0 ; den_ = 1 ; return *this;} // a/-Inf=0

        if ((num_ == 1 && den_ == 0) && (other.num_ < 0 && other.den_ != 0 )) {num_ = -1 ; den_ = 0 ; return *this;} // Inf/a=-Inf, a<0
        if ((num_ == -1 && den_ == 0) && (other.num_ < 0 && other.den_ != 0)) {num_ = 1 ; den_ = 0 ; return *this;} // -Inf/a=Inf
        
        if ((num_ == 0 && den_ == 1) && (other.num_ == 0 && other.den_ == 1)) {num_ = 0 ; den_ = 0 ; return *this;} // 0/0=NaN

        if ((num_ > 0 && den_ != 0) && (other.num_ == 0 && other.den_ == 1)) {num_ = 1 ; den_ = 0 ; return *this;} // a/0=Inf, a>0
        if ((num_ < 0 && den_ != 0) && (other.num_ == 0 && other.den_ == 1)) {num_ = -1 ; den_ = 0 ; return *this;} // a/0=-Inf, a<0


        num_ = num_ * other.den_ ;
        den_ = den_ * other.num_ ;
        simplify();

        return *this; 
    }
/* CANONICAL IMPLEMENTATION OF /  */
    rational operator/(const rational& other) const {

        rational rat = *this;
        rat = rat.operator/=(other);

        return rat;
    }

};



template<typename I>
std::ostream&

operator<<(std::ostream& os, const rational<I>& rat) {
    
    if (rat.num() == 0 && rat.den() == 1) {os << "0";}
    
    else if (rat.num() == 1 && rat.den() == 0) {os << "Inf";}

    else if (rat.num() == -1 && rat.den() == 0) {os << "-Inf";}

    else if (rat.num() == 1 && rat.den() == 0) {os << "Inf";}

    else if (rat.num() == 0 && rat.den() == 0) {os << "NaN";}

    else {os << rat.num() << "/" << rat.den();}

    return os;
}