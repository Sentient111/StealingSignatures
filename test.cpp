#include "SignatureDublication.h"


int main()
{
	//get file paths
	std::string targetPath;
	std::string addPath;

	std::cout << "Please enter path to Executable to steal the certificate from: ";
	std::cin >> targetPath;

	std::cout << "Please enter path to Executable to add certificate to: ";
	std::cin >> addPath;


	StealCertificateFromFile(targetPath, addPath);
	

	system("pause");
	return 0;
}
