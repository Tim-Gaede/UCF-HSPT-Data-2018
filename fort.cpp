#include <bits/stdc++.h>


int main(void) {
   int n;
   std::string tmp;

   // Get the number of passwords to check
   std::getline(std::cin, tmp);
   std::stringstream ss(tmp);
   ss >> n;

   // Loop over each password
   std::string pass;
   while (n--) {
      // Get the password
      std::getline(std::cin, pass);

      std::printf("%s\n", pass == "hey guys" ? pass.data() : "buzz");
   }

   return 0;
}
