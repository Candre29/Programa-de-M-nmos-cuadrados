// Jesús Emmanuel Sevilla Robles
// André Jerónimo López Nápoles

#include<iostream>
#include<iomanip> //Paa la presicion de los datos.
#include<cstdlib>
#include<stdlib.h>
#include<math.h> // Para exponenciales
#include<fstream>//Se utiliza para ficheros
#include<string>// Cadenas de caracteres
#include<stdio.h>
#define GNUPLOT_PATH "/usr/bin/gnuplot"
using namespace std;

int main (){
	
	int m,n,puntos;
	char letra;
	string deseo="no", leer="no",nombredelarchivo,prueba;
	string wish="nose";
	string pregunta="no"; 
	string name;
	char d='z';
	
	double *x,*y,*sx,*syx,sy[3],**matriz,**matrizinicial,resultado,*incognitas,r;
    void  evaluar(double **Matriz, int filas,double evaluado,double resultado);
	void reorganizadatos(double **matrizinicial,double *x,double *y,int n);
	
	ofstream plot; // script que servir� para graficar
	ofstream exportar;

	
	cout<<"Este programa utiliza el metodo de minimos cuadrados para hacer que pares coordenados se ajusten a una funcion de un grado determinado. Debes recordar que para ajustar a una funcion de grado n deberas proporcionar al menos n+1 pares coordenados. Una funcion de grado 1 corresponde a una recta. Una funcion de grado 2 corresponde a una parabola..."<<endl;
	
	 cout<<"\nIntroduzca una letra para continuar\n";
     cin>>letra;
     
	system("clear");
	
	
	cout<<"Desea la lectura de un archivo que contenga los pares coordenados? [si/no] (El archivo debera tener la extension .txt y solo debera contener los pares coordenados)"<<endl;
	cin>>leer;
	system("clear");
////////////////////////////////////////////////////////////////////////////////////////////////////////	
	if (leer=="si"){
		cout<<"Introduzca el nombre del archivo que contiene los datos, junto con la extension .txt (el archivo debera estar contenido en la carpeta del programa)."<<endl;
		cin>>nombredelarchivo;
		cout<<"\n"<<nombredelarchivo<<endl;
		system("clear");
		cout<<"Introduzca el numero de pares coordenados que contiene el archivo"<<endl;
		cin>>n;
		system ("clear");
		
		x= new double[n];
	    y= new double[n];
		matrizinicial= new double*[n];
		
		for(int on=0;on<n;on++){
			matrizinicial[on]=new double[2];
		}
		
		
	FILE *fichero; 
          
     fichero=fopen(nombredelarchivo.c_str(),"r");      
     if (fichero == NULL){
        printf("No se pudo abrir el archivo"); 
        exit(1);}
     else          
     {     
         for (int bb=0;bb<n;++bb)
         {           
            for (int jb=0;jb<2;++jb)
            {
               fscanf(fichero, "%lf", &matrizinicial[bb][jb]);                                  
                
             }
             
         }
         
        
          
      }
      reorganizadatos(matrizinicial,x,y,n);
      
       
    fclose(fichero);
    
		for(int dd=0;dd<n;dd++){
		delete[] matrizinicial[dd];
	}
	delete[] matrizinicial;
		
	fichero=NULL;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	else{
	ofstream tabla;
	tabla.open("Tabla de datos.txt",ios::out);
	
	cout<<"Introduzca el numero de pares coordenados que desea ajustar"<<endl;
	cin>>n;
	
	x= new double[n];
	y= new double[n];
    
	cout<<"Introduzca los elementos del eje x"<<endl;
		for (int i=0;i<n;i++){
		cin>>x[i];
		
		
	}
	
	
     system("clear");
	
		cout<<"Introduzca los elementos del eje y"<<endl;
		for (int i=0;i<n;i++){
		cin>>y[i];
		
		
	}
		tabla<<"x      "<<"y"<<endl;
			for (int i=0;i<n;i++){
		tabla<<x[i]<<"       "<<y[i]<<endl;
	}
	
	tabla.close();}
	
	
	
	 cout<<"Introduzca una letra para continuar\n";
     cin>>letra;
	system("clear");
	
	do{
	cout<<"Introduza el grado de la funcion  a la que desea realizar el ajuste. Recuerde que el grado 1 corresponde a una recta, el grado 2 a una parabola, etc."<<endl;
	cin>>m;
	
	if (m>(n-1)){
		cout<<"No puedes ajustar los datos a una funcion de ese grado"<<endl;
		 cout<<"Introduzca una letra para continuar\n";
         cin>>letra;
		system("clear");
	}}
	
	while(m>(n-1));
	
	system("clear");
	
	
	sx=new double[(2*m)+1];           // Declaracion de arreglos y matriz dinamicos. Los arreglos contendran los valores de las sumatorias y la matriz se utilzara
	syx= new double [m+1];         // para el sistema de ecuaciones normales.
    matriz= new double*[m+1];
    
    for(int p=0;p<(m+1);p++){
    	
    	matriz[p]= new double[m+2];
    	
    }

    
	
	for (int j=0;(j<=(2*m));j++){  //Realiza la sumatoria de los datos del eje x hasta un grado 2m
		for(int k=0;k<n;k++){
			sx[j]+=pow(x[k],j);
		}
	}
	
	
	for(int l=0;l<=m;l++){          // Realiza la sumatoria de la multiplicacion de las coordenadas  (y por x, y por x cuadrada...)  necesaras para cada grado seleccionado.
		for (int w=0;w<n;w++){
			syx[l]+=(pow(x[w],l)*y[w]);
		}
	}
	
	
	for(int y=0;y<=m;y++){              // Rellena el sistema de ecuaciones normales en forma matricial.
		for (int h=0;(h<=(m+1));h++){
     
	 		if(h<(m+1)){
			
			     matriz[y][h]=sx[h+y];			
			}
			
			
			else {
				matriz[y][h]=syx[y];
				
			}
	}		
	}
	

cout<<"El sistema de ecuaciones normales es el siguiente: "<<endl;

	
	for(int f=0;f<=m;f++){
		for(int d=0;d<=(m+1);d++){
			
			if (d<(m+1)){
				
			cout/*<<fixed<<std::setprecision(2)*/<<matriz[f][d]<<" a"<<d<<"     ";}
			
			else {
			cout<<" = "<</*fixed<<std::setprecision(2)<<*/matriz[f][d]<<" ";}
			
			
		}
		cout<<"\n";
	}
	
	
	
	
	for(int b=0;b<=m;b++){     //Este codigo corresponde al algoritmo Gauss-Joran normal. No se utilizan inversas ni sustitucion hacia atras.
	
	for(int t=(m+1);t>=0;t--){
		matriz[b][t]=((matriz[b][t])/(matriz[b][b]));
	}
	for (int n=0;n<=m;n++){
		if (n!=b){
			
			for(int t=(m+1);t>=0;t--){
		matriz[n][t]=((matriz[n][t])-((matriz[n][b]*matriz[b][t])));}
		}
	}
	
}





cout<<endl;


cout<<"Finalmente, la funcion correspondiente es:  "<<endl; //Despliega la funcion correspondiente en base a los resultados del sistema de ecuaciones.
cout<<"f(x)= ";
for(int kk=0;kk<=m;kk++){
	
	if(kk==0){
    cout<<matriz[kk][m+1]<<" + ";
	}
	
   else if((kk<m)&&(kk>0)
   ){
   cout<<matriz[kk][m+1]<<"x^"<<kk<<" + ";}

    else if (kk==m){
    cout<<matriz[kk][m+1]<<"x^"<<kk;
    }}
    
    
    cout<<endl;
    cout<<endl;

    if(m==1){
    	
    	
    		for (int j=0;j<=2;j++){  //Realiza la sumatoria de los datos del eje y hasta un grado 2
		for(int k=0;k<n;k++){
			sy[j]+=pow(y[k],j);
		}

	}
    	
    	
    	
    	
    	cout<<"Con un coeficiente de correlacion lineal r de " <<endl;
    	
    	r=(((n*syx[1])-(sx[1]*sy[1]))/((sqrt((n*sx[2])-(pow(sx[1],2))))*(sqrt((n*sy[2])-(pow(sy[1],2))))));
    	cout<<endl;
    	cout<<"r= "<<r<<endl;
    	
    	
    
    }
 ////////////////////////////////////////Plot//////////////////////////////////////////////// 
plot.open("Plot.gnu",ios::out);
    plot<<"set title \"Rayos X\""<<endl;
	plot<<"set key autotitle columnhead"<<endl;
	plot<<"set ylabel \"y\""<<endl;
	plot<<"set xlabel \"x\""<<endl;
	plot<<"plot ";
    for(int kk=0;kk<=m;kk++){
	if(kk==0){
    plot<<matriz[kk][m+1]<<" + ";
	}
	
   else if((kk<m)&&(kk>0)
   ){
   plot<<matriz[kk][m+1]<<"*x**"<<kk<<" + ";}

    else if (kk==m){
    plot<<matriz[kk][m+1]<<"*x**"<<kk;
    }}
    
    if(leer=="si"){
    plot<<" w l lt 7 linecolor \"red\","<<"\""<<nombredelarchivo<<"\" pt 7"; 
    
			      }
    else{ 
		plot<<" w l lt 7 linecolor \"red\", \"Tabla de datos.txt\" pt 7  ";
		}
   
    plot.close();
    
    
    cout<<"\nDesea graficar la recta y los puntos? si/no \n";
							      cin>>wish;
							      if(wish=="si"){    
							      FILE *pg;
                                      pg=popen(GNUPLOT_PATH,"w");
                                      fprintf(pg,"load \"Plot.gnu\" \n");   
							          fflush(pg);
							          
							          while(d!='x'){
                                       cout<<"Introduzca 'x' para continuar\n";
                                       cin>>d; 
												   }                                            
								                                                                         
                                      pclose(pg);                                
											    }
		cout<<"\nDesea guardar la grafica? \t si/no\n";
            cin>>pregunta;
            if(pregunta=="si"){
	         cout<<"\nComo quiere llamar a la grafica\nEn vez de usar espacios use guion, ejemplo: luz-solar\n";
	         cin>>name;
	 
	         exportar.open("Exportar.gnu",ios::out);
	          exportar<<"set term png"<<endl;
	          exportar<<"set title "<<"\""<<name<<"\""<<endl;
	          exportar<<"set output "<<"\""<<name<<".png"<<"\""<<endl;
	          /*exportar<<"unset output "<<endl;
	          exportar<<"unset term "<<endl;*/
             exportar.close();
                               
                             FILE *pg;  
                             pg=popen(GNUPLOT_PATH,"w");       
                              fprintf(pg,"load \"Exportar.gnu\" \n"); 
                              fprintf(pg,"load \"Plot.gnu\" \n");     
							  fflush(pg);                                                                         
                                 
                             pclose(pg);          
                                 }   
 
 
 
 ////////////////////////////////////////Plot//////////////////////////////////////////////// 
    


    cout<<endl;
	cout<<"Introduzca una letra para continuar\n";
    cin>>letra;
	system("clear");

    cout<<"�Desea evaluar puntos en la funcion (si/no)?"<<endl;
    cin>>deseo;
    
    if (deseo=="si"){
    
	  cout<<"�Cuantos puntos desea evaluar en la funcion?"<<endl;
	  cin>>puntos;
	  
	  incognitas= new double[puntos];

	  
	  
	  for (int u=0;u<puntos;u++){
	  	cout<<"Digite el punto numero "<<u+1<<endl;
	  	cin>>incognitas[u];
	  	
	  }
	  
	  system("clear");
	  
	  
	   for(int j=0;j<puntos;j++){
	   	cout<<incognitas[j]<<" => ";
	   	evaluar(matriz,m,incognitas[j],resultado=0);
	   	
	   	
	   	
	   	
	   }  delete[] incognitas;   }
	  
	  
	  else{
	  	cout<<"Gracias por utilizar el programa"<<endl;
	  }
	  
	  
	  
	
	
	
	
	
	delete[] x;
	delete[] y;
	delete[] sx;
	delete[] syx;
	
	
	
	for(int z=0;z<(m+1);z++){
		delete[] matriz[z];
	}
	
	delete[] matriz;
	
	
	
	
	
	return 0;
}

    void  evaluar(double **Matriz, int filas,double evaluado,double resultado=0){
    
    for(int tt=0;tt<=filas;tt++){
    	resultado+=((pow(evaluado,tt))*(Matriz[tt][filas+1]));
    	
    }
    cout<<resultado<<endl;
    resultado=0;
    
}


	void reorganizadatos(double **matrizinicial,double *x,double *y,int n){
		
		for (int i=0;i<n;i++){
			for(int j=0;j<n;j++){
			 x[j]=matrizinicial[j][0];
			 y[j]=matrizinicial[j][1];
			}
		}
		
		
		
		
	}

