void HiSPECTtoGate() {

  char temp_str[64];
  
  int n_pinholes;
  float x, y;
  float dia, cone_angle;
  float px, py;
  float  angle;
  float phi, theta;

  // open pinhole description file

  ///************ Part To Adapt***************///
  //Use your input file with .hispect extention 
  string inputname="APT1.hispect";
  std::ifstream fin;
  fin.open(inputname);
  
  ///************ Part To Adapt***************///
  //Use your rotation radius as z 
  // float z =  45.f; //APT2
  float z =  30.f; //APT1

  ///************ Part To Adapt***************///
  //Use your collimator thickness devided by 2 as h 
  float h = 10./2.; //10 mm
  
  string outputname=inputname.erase(inputname.find(".hispect"),8)+"_hispect.pin";
  std::ofstream fout;
  fout.open(outputname);

  // parse file
  fin >> temp_str;
  if (temp_str[0] == '#')
		fin.ignore(256,'\n'); // ignore first line if it starts with #

	fin >> temp_str;
	if(temp_str[0] == '[')
		std::cout << "\nLoading pinhole definition " << temp_str << std::endl;
	else
	{
		std::cout << "\nInvalid pinhole definition file." << std::endl;
		fin.close();
		return NULL;
	}

	fin >> n_pinholes;

	float apex;

	fout<<"# x y dia  alpha_cone x_focal y_focal"<<endl;
	fout<<temp_str<<endl;
	fout<<n_pinholes<<endl;
	
	for(int i=0;i<n_pinholes;i++)
	{
	  
	  fin >> x >> y >> dia  >> angle >> phi >> theta;

	  cout<<i+1<<endl;	  

	  float l=z*tan(theta*4.0f * atan(1.0f) / 180.0f);
	  float dx=l*cos(phi*4.0f * atan(1.0f) / 180.0f );
	  float dy=l*sin(phi*4.0f * atan(1.0f) / 180.0f );


	   px=x-dx;
	   py=y-dy;

	   if (fabs(py)<0.001 )
	     py=0;
	   cout<<x<<" --> "<<px<<endl;
	   cout<<y<<" --> "<<py<<endl;


	  fout<< x<<" "<<y<<" "<<dia<<" "<<angle/2<<" "<<px<<" "<<py<<endl;
	}

	fin.close();

	fout.close();
	return false;
}
