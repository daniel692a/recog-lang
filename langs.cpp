#include <array>
#include <bits/stdc++.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

using namespace std;

void create_write_file(string name){
	// Declare two files with fstream class
	fstream new_file, bash_script;
	// new_file -> Our code file
	new_file.open(name, ios::out);
	// boolean operation
	if (!new_file.is_open()) {
		cout<<"Error al abrir el archivo\n";
	} else {
		cout<<"Ahora escribe en el archivo\n";
		// text -> text to write in the file
		string text = "";
		// add -> save an answer to add more
		string add="";

		do {
			// noskipws -> don't ignore leading whitespaces, don't trim
			getline(cin>>noskipws, text);
			text+="\n";
			new_file.write(text.data(), text.size());
			cout<<"¿Deseas añadir otra linea?\nsi\to no\n";
			getline(cin, add);
		}while (add == "si");
		// answer -> Open code editor
		string answer = "";
		cout<<"¿Deseas abrir un editor de texto para continuar?\n";
		getline(cin, answer);

		if(answer=="si"){
			// Open a bash script to run commands
			bash_script.open("launch.sh", ios::out);

			if(!bash_script.is_open()){
				cout<<"Error al abrir"<<endl;
			}else {
				// save your editor
				string editor = "";
				cout<<"Escribe nombre del editor: ";
				cin>>editor;
				// write the command
				string command = editor + " " + name;
				bash_script.write(command.data(), command.size());
			}

			new_file.close();
			bash_script.close();
			// execute the bash script
			system("./launch.sh");

		}else{
			cout<<"Hasta luego:)";
		}
		new_file.close();
	}
}

string detect_lang(string ext){
	// Compare programming languages
	// Show an example
	if(ext=="js"){
		return "JavaScript -> console.log(\"Hello, World!\");\n";
	} else if (ext=="cpp") {
		return "C++ -> cout << \"Hello, World!\"\n;";
	} else if (ext == "py") {
		return "Python -> print(\"Hello World!\")\n";
	} else if (ext=="rb") {
		return "Ruby -> puts \"Hello, World!\"\n";
	} else if (ext=="hs") {
		return "Haskell -> main = putStrLn \"Hello, World!\"\n";
	} else if (ext=="rs") {
		return "Rust -> println!(\"Hello, World!\");\n";
	} else if (ext=="jl") {
		return "Julia -> print(\"Hello, World!\")\n";
	} else if (ext=="c") {
		return "C -> printf(\"Hello, World!\");\n";
	} else if(ext=="cs"){
		return "C# -> Console.WriteLine(\"Hello, World!\");\n";
	} else {
		return "Unknow element:(\n";
	}
}

int main(){
	string filename;

	do {
		cout<<"Escribe un nombre valido para el archivo: ";
		getline(cin, filename);
	}while (!regex_match(filename, regex("[a-zA-Z_0-9]*\\.[a-zA-Z]{1,3}")));
	// get extension
	int count_ext = 0;
	// O(n) -> worst case
	for(int i=filename.length()-1; i>0; i--){
		// 46 -> "."
		// Find the dot
		if(filename[i]!=46){
			count_ext++;
		} else{
		// Break the loop
			break;
		}
	}
	// Call detect_lang function
	// Create a substring after the dot at the end
	cout<<"Archivo de tipo "<<detect_lang(filename.substr(filename.length()-count_ext, count_ext));
	// Write over file
	create_write_file(filename);
	return 0;
}
