#ifndef PLAYER_H // Usar #ifndef y #define para proteger el archivo de encabezado
#define PLAYER_H

#include <string>

class player {
	private:
		std::string user;
		int pass;
		int id;
	public:
		int toros;
		int vacas;
		int level;
		int intentos;
		int code;
		
	player(std::string u = "Anonimo", int p = 0, int i = 0, int t = 0, int v = 0, int l = 3, int in = 0, int c = 0)
        : user(u), pass(p), id(i), toros(t), vacas(v), level(l), intentos(in), code(c) {}
        
    void setUser(const std::string& u) {
        user = u;
    }

    void setPass(int p) {
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

    void setCode(int c) {
        code = c;
    }

    // Getters
    std::string getUser() const {
        return user;
    }

    int getPass() const {
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

    int getCode() const {
        return code;
    }
};

player findPlayerById(int searchId);

#endif // Termina la protección del archivo de encabezado
