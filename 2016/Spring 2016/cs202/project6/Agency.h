class Car{

public:
	Car();
	Car(char *, char *, int, float, bool);
	Car(const Car&);
	~Car();

	void copy(Car);
	void print() const;

	char * getMake() const;
	char * getModel() const;
	int getYear() const;
	float getPrice() const;
	bool getAvailable() const;

	void setMake(char *);
	void setModel(char *);
	void setYear(int);
	void setPrice(float);
	void setAvailable(bool);

private:
	char * make;
	char * model;
	int year;
	float price;
	bool available;
};


class Agency{

public:

	Agency();
	Agency(const Agency&);
	~Agency();

	void readInData(char *);

	void print() const;
	void printAvailableCars() const;

	void findMostExpensive() const;
	float estimateCost(int, int) const;

	void sortByMake();    // alphabetical
	void sortByPrice();   // highest to lowest

	void searchByMake(char *) const;

private:

	char * name;
	int * zipcode;
	Car * inventory;

};
