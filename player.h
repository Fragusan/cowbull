#ifndef PLAYER_H // Usar #ifndef y #define para proteger el archivo de encabezado
#define PLAYER_H

#include <string>

class player {
private:
    std::string user;
    std::string pass;
    int id;
public:
    int toros;
    int vacas;
    int level;
    int intentos;
    std::string code;

    player(std::string u = "Anonimo", std::string p = "0", int i = 0, int t = 0, int v = 0, int l = 3, int in = 0, std::string c = "0")
        : user(u), pass(p), id(i), toros(t), vacas(v), level(l), intentos(in), code(c) {}

    // Getters
    std::string getUser() const {
        return user;
    }

    std::string getPass() const {
        return pass;
    }

    int getId() const {
        return id;
    }

    int getToros() const {
        return toros;
    }

    int getVacas() const {
        return vacas;
    }

    int getLevel() const {
        return level;
    }

    int getIntentos() const {
        return intentos;
    }

    std::string getCode() const {
        return code;
    }

    // Setters
    void setUser(const std::string& u) {
        user = u;
    }

    void setPass(const std::string& p) {
        pass = p;
    }

    void setId(int i) {
        id = i;
    }

    void setToros(int t) {
        toros = t;
    }

    void setVacas(int v) {
        vacas = v;
    }

    void setLevel(int l) {
        level = l;
    }

    void setIntentos(int in) {
        intentos = in;
    }

    void setCode(const std::string& c) {
        code = c;
    }
};

player findPlayerById(int searchId);

/*
se intento con valores predeterminados por defecto, pero no los tomo
void updatePlayer(int updateId, const std::string &newUser = "", const std::string &newPass = "", int newToros = -1,
                  int newVacas = -1, int newLvl = -1, int newIntentos = -1, const std::string &newCode = "");
				  
*/



#endif // Termina la protección del archivo de encabezado
