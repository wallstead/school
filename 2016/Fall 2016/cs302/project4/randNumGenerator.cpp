#include <iostream>
#include <fstream>

void populateFile(int count, std::string const& file) {
    std::ofstream myfile(file);
    if (!myfile) {
       return;
    }

    for(int index=0; index<count; index++) {
        int random_integer = (rand()%1000000)+1;
        myfile << random_integer << "\n";
    }
}

int main(){
   // Seed the random number generator.
   srand( time( NULL ) );

   // Populate the file
   std::string file("rand_1,000,000");
   populateFile(1000000, file);

   return 0;
}
