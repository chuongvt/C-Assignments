/*Complex.java
 * Chuong Viet Truong
 * chvtruon
 * pa6
 * Arithmetic and algebraic properties of complex numbers
 */

class Complex{

   private double re;
   private double im;
   
   public static final Complex ONE = Complex.valueOf(1,0);
   public static final Complex ZERO = Complex.valueOf(0,0);
   public static final Complex I = Complex.valueOf(0,1);

   Complex(double a, double b){
      this.re = a;
      this.im = b;
   }

   Complex(double a){
      this.re = a;
      this.im = 0;
   }

   Complex(String s){
	   double[] C = parseComplex(s);
	   this.re = C[0];
	   this.im = C[1];
   }
   
   static double[] parseComplex(String str){
	      double[] part = new double[2];
	      String s = str.trim();
	      String NUM = "(\\d+\\.\\d*|\\.?\\d+)";
	      String SGN = "[+-]?";
	      String OP =  "\\s*[+-]\\s*";
	      String I =   "i";
	      String OR =  "|";
	      String REAL = SGN+NUM;
	      String IMAG = SGN+NUM+"?"+I;
	      String COMP = REAL+OR+
	                    IMAG+OR+
	                    REAL+OP+NUM+"?"+I;
	      
	      if( !s.matches(COMP) ){
	         throw new NumberFormatException(
	                   "Cannot parse input string \""+s+"\" as Complex");
	      }
	      s = s.replaceAll("\\s","");     
	      if( s.matches(REAL) ){
	         part[0] = Double.parseDouble(s);
	         part[1] = 0;
	      }else if( s.matches(SGN+I) ){
	         part[0] = 0;
	         part[1] = Double.parseDouble( s.replace( I, "1.0" ) );
	      }else if( s.matches(IMAG) ){
	         part[0] = 0;
	         part[1] = Double.parseDouble( s.replace( I , "" ) );
	      }else if( s.matches(REAL+OP+I) ){
	         part[0] = Double.parseDouble( s.replaceAll( "("+REAL+")"+OP+".+" , "$1" ) );
	         part[1] = Double.parseDouble( s.replaceAll( ".+("+OP+")"+I , "$1"+"1.0" ) );
	      }else{   //  s.matches(REAL+OP+NUM+I) 
	         part[0] = Double.parseDouble( s.replaceAll( "("+REAL+").+"  , "$1" ) );
	         part[1] = Double.parseDouble( s.replaceAll( ".+("+OP+NUM+")"+I , "$1" ) );
	      }
	      return part;
   }

   Complex copy(){
	   return new Complex(this.re, this.im);
   }
   
   Complex add(Complex z){
	   return new Complex(this.re+z.re, this.im+z.im);
   }
   
   Complex negate(){
	   return new Complex(-this.re, -this.im);
   }

   Complex sub(Complex z){
	   return new Complex(this.re-z.re, this.im-z.im);
   }

   Complex mult(Complex z){
	   return new Complex((this.re*z.re)-(this.im*z.im), (this.re*z.im)+(this.im*z.re));
   }

   Complex recip(){
	   if (this.equals(Complex.ZERO)) {
		   throw new ArithmeticException("Cannot divide by 0");
	   }
	   double a = ((this.re*this.re)+(this.im*this.im));
	   return new Complex((this.re)/(a), (-this.im)/(a));
   }

   Complex div(Complex z){
	   if (z.equals(Complex.ZERO)) {
		   throw new ArithmeticException("Cannot divide by 0");
	   }
	   double d = (z.re*z.re)+(z.im*z.im);
	   return new Complex(((z.re*this.re)+(z.im*this.im))/d, ((z.re*this.im)-(z.im*this.re))/d);
   }

   Complex conj(){
	   return new Complex(this.re, -this.im);
   }
   
   double Re(){
      return re;
   }
   
   double Im(){
      return im;
   }

   double abs(){
	   return Math.sqrt((this.re*this.re)+(this.im*this.im));
   }

   double arg(){
      return Math.atan2(im, re);
   }
 
   public String toString(){
 		if ((this.im > 0 && this.re > 0) || ( this.im > 0 && this.re < 0)){
   			return this.re+"+"+this.im+"i";
   		}
  		else if ((this.im < 0 && this.re < 0) || (this.im < 0 && this.re > 0)){
   			return +this.re+"-"+(-this.im)+"i";
   		}
  		else if ((this.im == 0 && this.re < 0) || (this.im == 0 && this.re > 0)){
   			return this.re+" ";
   		}
   		return +this.im+"i";
   }

   public boolean equals(Object obj){
	   Complex x;
	   boolean eq = false;
	   if (obj instanceof Complex) {
		   x = (Complex) obj;
		   eq = (this.re == x.re) && (this.im == x.im);
	   }
	   return eq;
   }

   static Complex valueOf(double a, double b){
	   return new Complex(a, b);
   }

   static Complex valueOf(double a){
	   return new Complex(a);
   }

   static Complex valueOf(String s){
	   return new Complex(s);
   }

}
