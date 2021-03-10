#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <map>
#include <vector>

using namespace std;

int n = 0;			//amount of points

struct node {
	string name_node;  //shape
	string w_type;		//type 
	string name_type;	//tetrahedron
	string w_vertices;	//vertices 
	struct vertices {
		string w_point;		// point 
		string x, y, z, v_x, v_y, v_z;
	};
	vertices* ver = new vertices[n];
	string w_color;
	struct color {		//color 
		string r, g, b, alpha, v_r, v_g, v_b, v_alpha;
	};
	color col;
};
int getpoints(string &filename, int& n);		// get amount of points
void getinfo(string &filename, node& nod, multimap <int, int>& id, int &n, vector <int>& n_name_node, vector <int>& n_vertices,
	vector <int>& n_color, multimap <int, int>& n_point);	//get information from input file
void setinfo(string &filename, node& nod, multimap <int, int>& id, int& n, vector <int>& n_name_node, vector <int>& n_vertices,
	vector <int>& n_color, multimap <int, int>& n_point);	//set information to output file

int main()
{	
	multimap <int, int> id, 
		num_point;		//num_* child id
	vector <int> num_name_node, num_vertices, num_color;
	string filename1, filename2;		// input and output file names
	
	cout << "set input file and press Enter" << endl;
	getline(cin,filename1);
	cout << "set output file and press Enter" << endl;
	getline(cin, filename2);

	getpoints(filename1, n);
	
	node a; //structure object

	getinfo(filename1,a, id, n, num_name_node, num_vertices, num_color, num_point);
	setinfo(filename2, a, id, n, num_name_node, num_vertices, num_color, num_point);
	cout << "performed" << endl;
	return 0;
}
int getpoints(string& filename, int& n)
{

	ifstream file(filename, ios::in);
	if (!file.is_open())
	{
		std::cerr << "Unable to open file\n";
		exit(1);
	}
	n = 0;
	for (n; !file.eof();)
	{
		string temp;
		file >> temp;
		if (temp == "point")
			n++;
	}
	return n;
}

void getinfo(string &filename, node& nod, multimap <int, int> &id, int &n, vector <int> &n_name_node, vector <int> &n_vertices,
	vector <int> &n_color, multimap <int, int> &n_point)
{

	ifstream file(filename, ios::in);
	if (!file.is_open())
	{
		cerr << "Unable to open file\n";
		exit(1);
	}
	while ( !file.eof())
	{
		int id_name_node = 1;
		getline(file, nod.name_node, ' ');

		if (isdigit(nod.name_node[0]))
		{
			cerr << "invalid data format\n";
			exit(1);
		}
		id.insert(make_pair(id_name_node, id_name_node - 1));
		file.ignore(4);

		getline(file, nod.w_type, ' ');

		if (isdigit(nod.w_type[0]))
		{
			cerr << "invalid data format\n";
			exit(1);
		}

		file.ignore(3);
		
		getline(file, nod.name_type, '"');
		int id_name_type = 2;

		for (int i = 0; i < nod.name_type.size(); i++)
		{
			if ((nod.name_type[i])=='\n')
			{
				cerr << "invalid data format\n";
				exit(1);
			}
		}
		n_name_node.push_back(id_name_type);
		id.insert(make_pair(id_name_type, id_name_type - 1));
		file.ignore(1);
		
		getline(file, nod.w_vertices, ' ');
		
		if (isdigit(nod.w_vertices[0]))
		{
			cerr << "invalid data format\n";
			exit(1);
		}

		int id_w_vertices = 3;
		n_name_node.push_back(id_w_vertices);
		id.insert(make_pair(id_w_vertices, id_w_vertices - 2));
		file.ignore(4);
		
		int id_w_point = 4;
		int j = 4;
		for (int i = 0; i < n;)
		{
			getline(file, nod.ver[i].w_point, ' ');
			
			if (isdigit(nod.ver[i].w_point[0]))
			{
				cerr << "invalid data format\n";
				exit(1);
			}
			id.insert(make_pair(id_w_point, id_w_vertices));
			n_vertices.push_back(id_w_point);
			file.ignore(4);

			getline(file, nod.ver[i].x, ' ');
			id.insert(make_pair(j + 1, id_w_point));
			n_point.insert(make_pair(i, j + 1));
			file.ignore(3);

			getline(file, nod.ver[i].v_x, '"');
			for (int j = 0; j < nod.ver[i].v_x.size(); j++)
			{
				if ((nod.ver[i].v_x[j]) == '\n')
				{
					cerr << "invalid data format\n";
					exit(1);
				}
			}
			file.ignore(1);

			getline(file, nod.ver[i].y, ' ');
			id.insert(make_pair(j + 2, id_w_point));
			n_point.insert(make_pair(i, j + 2));
			file.ignore(3);

			getline(file, nod.ver[i].v_y, '"');
			for (int j = 0; j < nod.ver[i].v_y.size(); j++)
			{
				if ((nod.ver[i].v_y[j]) == '\n')
				{
					cerr << "invalid data format\n";
					exit(1);
				}
			}
			file.ignore(1);

			getline(file, nod.ver[i].z, ' ');
			id.insert(make_pair(j + 3, id_w_point));
			n_point.insert(make_pair(i, j + 3));
			file.ignore(3);

			getline(file, nod.ver[i].v_z, '"');
			for (int j = 0; j < nod.ver[i].v_z.size(); j++)
			{
				if ((nod.ver[i].v_z[j]) == '\n')
				{
					cerr << "invalid data format\n";
					exit(1);
				}
			}
			file.ignore(3);
			
			i++;
			j = j + 4;
			id_w_point = id_w_point+4;
		}
		file.ignore(2);
		getline(file, nod.w_color, ' ');
	
		if (isdigit(nod.w_color[0]))
		{
			cerr << "invalid data format\n";
			exit(1);
		}
		id.insert(make_pair(j, id_name_node));
		n_name_node.push_back(j);
		file.ignore(4);

		getline(file, nod.col.r, ' ');
		id.insert(make_pair(j+1, j));
		n_color.push_back(j + 1);
		file.ignore(3);
		getline(file, nod.col.v_r, '"');
		for (int j = 0; j < nod.col.v_r.size(); j++)
		{
			if ((nod.col.v_r[j]) == '\n')
			{
				cerr << "invalid data format\n";
				exit(1);
			}
		}
		file.ignore(1);

		getline(file, nod.col.g, ' ');
		id.insert(make_pair(j + 2, j));
		n_color.push_back(j + 2);
		file.ignore(3);
		getline(file, nod.col.v_g, '"');
		for (int j = 0; j < nod.col.v_g.size(); j++)
		{
			if ((nod.col.v_r[j]) == '\n')
			{
				cerr << "invalid data format\n";
				exit(1);
			}
		}
		file.ignore(1);

		getline(file, nod.col.b, ' ');
		id.insert(make_pair(j + 3, j));
		n_color.push_back(j + 3);
		file.ignore(3);
		getline(file, nod.col.v_b, '"');
		for (int j = 0; j < nod.col.v_r.size(); j++)
		{
			if ((nod.col.v_r[j]) == '\n')
			{
				cerr << "invalid data format\n";
				exit(1);
			}
		}
		file.ignore(1);

		getline(file, nod.col.alpha, ' ');
		id.insert(make_pair(j + 4, j));
		n_color.push_back(j + 4);
		file.ignore(3);
		getline(file, nod.col.v_alpha, '"');
		for (int j = 0; j < nod.col.v_r.size(); j++)
		{
			if ((nod.col.v_r[j]) == '\n')
			{
				cerr << "invalid data format\n";
				exit(1);
			}
		}
		file.ignore(5);
	}
	file.close();
}


void setinfo(string& filename, node& nod, multimap <int, int>& id, int& n, vector <int>& n_name_node, vector <int>& n_vertices,
	vector <int>& n_color, multimap <int, int> &n_point)
{
	ofstream out(filename);
	if (!out.is_open())
	{
		std::cerr << "Unable to open file\n";
		exit(1);
	}
		for (auto it = id.begin(); it != id.end(); )
		{
			out << it->first << ", " << it->second << ", " << nod.name_node << ", ";
			for (int i = 0; i < size(n_name_node); i++)
			{
				out << n_name_node[i] << " ";
			}
			out << endl;
			it++;
			out << it->first << ", " << it->second << ", " << nod.w_type << ", " << nod.name_type << endl;
			it++;
			out << it->first << ", " << it->second << ", " << nod.w_vertices << ", ";
			for (int i = 0; i < size(n_vertices); i++)
			{
				out << n_vertices[i] << " ";
			}
			out << endl;
			it++;
			for (int i = 0; i < n; i++)
			{

				out << it->first << ", " << it->second << ", " << nod.ver[i].w_point << ", ";
				
				for (int j=i; j < n; )
				{
					pair <multimap<int, int>::iterator, multimap<int, int>::iterator> ret;
					ret = n_point.equal_range(j);
					
						for (multimap<int, int>::iterator t = ret.first; t != ret.second; ++t)
						{	
							out << ' ' << t->second;
							j++;
						}
					out << '\n';
					break;
				}

				it++;
				out << it->first << ", " << it->second << ", " << nod.ver[i].x << ", " << nod.ver[i].v_x << endl;
				it++;
				out << it->first << ", " << it->second << ", " << nod.ver[i].y << ", " << nod.ver[i].v_y << endl;
				it++;
				out << it->first << ", " << it->second << ", " << nod.ver[i].z << ", " << nod.ver[i].v_z << endl;
				it++;
			}
			out << it->first << ", " << it->second << ", " << nod.w_color << ", ";
			for (int i = 0; i < size(n_color); i++)
			{
				out << n_color[i] << " ";
			}
			out << endl;
			it++;
			out << it->first << ", " << it->second << ", " << nod.col.r << ", " << nod.col.v_r << endl;
			it++;
			out << it->first << ", " << it->second << ", " << nod.col.g << ", " << nod.col.v_g << endl;
			it++;
			out << it->first << ", " << it->second << ", " << nod.col.b << ", " << nod.col.v_b << endl;
			it++;
			out << it->first << ", " << it->second << ", " << nod.col.alpha << ", " << nod.col.v_alpha << endl;
			it++;
		}
}