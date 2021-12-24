#include "interface.h"

#include <iostream>
#include <vector>
const std::string lozenec =
"Uspeshnia - Gosho \n"
"Uspeshnia - Misho \n"
"Gosho     - Pesho \n"
"Gosho     - Dancho\n"
"Pesho     - Alex  \n"
"Dancho    - Boris \n"
"Dancho    - Kamen \n"
"Uspeshnia - Slavi \n"
"Slavi     - Slav1 \n"
"Slavi     - Slav2 \n"
"Slav1     - Mecho \n"
"Mecho     - Q12Adl\n";

int main() {
	Hierarchy h(lozenec);
	//std::cout << h.longest_chain() << std::endl;
	//std::cout << h.getSalary("Gosho");
	//std::cout << h.num_subordinates("Uspeshnia");
	//std::cout << h.print() << std::endl;
	//std::cout << h.getEmployeeLevel("Q12Adl");
	Hierarchy joined = h.join(h);
	std::cout << joined.print() << std::endl;
	//for (Hierarchy::Iter it = h.begin(); it != h.end(); ++it) {
	//	std::cout << it->getName() << std::endl;
	//}
}
