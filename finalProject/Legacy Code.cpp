std::string xmlParse(std::ifstream & infile, std::string idLookup)
{
	std::string fileData = "";
	char lineData[50] = "";

	while (!infile.eof())
	{
		std::getline(infile, fileData);
		memset(lineData, 0, 50);

		for (int i = 0; i < fileData.length(); i++)
		{
			lineData[i] = fileData.at(i);
		}

		if (idCheckup(fileData, lineData) == idLookup)
		{
			std::cout << idLookup << " FOUND" << std::endl;
		}
		else
		{
			std::cout << idLookup << " NOT FOUND" << std::endl;
		}
	}

	std::cout << std::endl;

	return "";
}// end of xmlParse

std::string idCheckup(std::string fileData, char elementData[])
{
	std::string id = "";

	for (int j = 0; j < fileData.length(); j++)
	{

		if (elementData[j] == 105 && elementData[j + 1] == 100 && elementData[j + 2] == 61 && elementData[j - 1] == 32)
		{

			int idIndex = j + 4;
			while (elementData[idIndex] != 34)
			{
				id += elementData[idIndex];
				idIndex++;
			}

			return id;
		}
	}

	return "";
}// end of idCheckup