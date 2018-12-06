int qtd_d(DATA dat, DATA datf){
	int qtd = 0;
	int i,j,k,l,m,x=0;

	// CALCULAR DATAS NO MESMO MES

	if(datf.m == dat.m && datf.a == dat.a){
		qtd = datf.d - dat.d; 
		return qtd;
	}

	// CALCULAR DATAS COM MAIS DE UM ANO
	
	if(datf.m == dat.m && datf.a != dat.a){
		int a = abs(datf.a - dat.a) + 1;
		int bi = 0;
		
		for(i=dat.a; i<datf.a; i++){
			if(bissexto(i))
				bi++;
		}

		qtd = ((datf.a - dat.a)*365) + (datf.d - dat.d) + bi; 
		
		if(bissexto(dat.a)){
			if(dat.m == 2){
				if(dat.d > 28)
					qtd--;
			}
			if(dat.m > 2)
				qtd--;
		}

		return qtd;
	}
	
	//CALCULAR DATAS NO MESMO ANO

	if(datf.a == dat.a){
		m = datf.m - dat.m + 1;
		
		int v[m]; int fev;
		
		if(bissexto(datf.a))
			fev = 29;
		else
			fev = 28;

		j=0;
		
		for(i = dat.m; i <= datf.m; i++){			
			v[j] = mes_d(i, fev);
			j++;
		}
		
		for(i = dat.d; i<v[0]; i++){
			qtd++;
		}
		
		i=dat.m;
	
		for(j=1; j<m || x==0 ;j++){
			i++;
			for(k=0; k<v[j];k++){
				qtd++;
				if(datf.d == k+1 && datf.m == i){
					x=1; break;
				}
			}			
		}
		return qtd;
	}

	// CALCULAR QUALQUER DATA
	
	if(dat.a != datf.a && dat.m != datf.m){
		
		int a = datf.a - dat.a + 1;
		
		m = abs(datf.m - dat.m) + 1;
		
		int mes = 12 - dat.m + 1;
		int v[mes], fev;

		if(bissexto(datf.a))
			fev = 29;
		else
			fev = 28;

		// CALCULAR A QUANTIDADE DE DIAS NO PRIMEIRO MES DE RESERVA
		
		j=0;

		for(i=dat.m;i<13;i++){
			v[j] = mes_d(i, fev);
			j++;
		}

		for(i=dat.d; i<v[0]; i++){
			qtd++;
		}
			
		//CALCULAR A QUANTIDADE DE DIAS A PARTIR DO SEGUNDO MES NO MESMO ANO
		
		l=1;
		
		for(i=dat.m+1; i<13 ;i++){			
			for(j=0; j<v[l]; j++){
				qtd++;
			}
			l++;						
		}

		//CALCULAR A QUANTIDADE DE MESES DO PROXIMO ANO

		j=1;
		int meses=0;
		
		for(i = dat.a + 1 ; i < datf.a + 1 || x==0 ; i++){
			for(j=1;j<13;j++){
				meses++;
				if(datf.m == j && datf.a == i){
					x=1;
					break;
				}				
			}		
		}

		int v2[meses];
		j=0;

		for(k = dat.a + 1 ; k < datf.a + 1 || x==0 ; k++){
			
			if(bissexto(k)){
				fev = 29;
			}
			else{
				fev = 28;
			}

			for(i=1;i<13;i++){
				v2[j] = mes_d(i, fev);
			
				if(datf.m == j && datf.a == i){
					x=1;
					break;
				}
				j++;				
			}		
		}

		//CALCULAR A QUANTIDADE DE DIAS DOS PROXIMOS ANOS DE RESERVA
		
		x=0; l=0; int qtd_t=0;
		
		for(i=dat.a+1; i <= datf.a;i++){
		
			for(j=1;j<13;j++){
				
				for(k=1; k<v2[l]+1;k++){					
					qtd_t++;					
					if(datf.d==k && datf.m == j && datf.a == i){
						x=1;
						break;
					}
				}
				l++;
				if(x==1)
					break;
			}
			if(x==1)
				break;
		}
		return qtd+qtd_t;
	}
}