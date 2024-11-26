import java.math.BigInteger;

class Test{
	public static void main(String[] args) {
		BigInteger A = new BigInteger("2989540626429799377152730000884577418714682383919291882126");
		BigInteger B = new BigInteger("5774187146823839192918821268");

		System.out.println("Result: "+ A.divide(B));

		// BigInteger betterNumerator = new BigInteger("993399393090909099393090");
		// BigInteger possibleDivisor = B;

		// int trailingZeros = A.toString().length() - betterNumerator.toString().length() - 1;
		// // double zeros = ;
		// String zerosString ="1";
		// for (int i = 0; i < trailingZeros; i++) {
		// 	zerosString +="0";
		// }
		// BigInteger zeros = new BigInteger(zerosString);
		// BigInteger closer_product = possibleDivisor.multiply(new BigInteger("29").multiply(zeros));
		// BigInteger remaining = A.subtract(closer_product);
		// Boolean eq = A.equals(remaining.add(closer_product));


		// System.out.println("product: "+ closer_product);
		// System.out.println("Remaining: "+ remaining);
		// System.out.println("product + remaining: " + closer_product.add(remaining));
		// System.out.println("Trailing Zeros: "+ trailingZeros);
		// System.out.println("Zeros:"+ zeros);
		// System.out.println("Equals:" + eq );


		// int trailingZeros2= 65 - betterNumerator.toString().length() - 1;
		// String zerosString2 ="1";
		// for (int i = 0; i < trailingZeros2; i++) {
		// 	zerosString2 +="0";
		// }
		// BigInteger zeros2 = new BigInteger(zerosString2);
		// BigInteger closer_product2 = possibleDivisor.multiply(new BigInteger("2988").multiply(zeros2));
		// BigInteger remaining2 = A.subtract(closer_product2);
		// Boolean eq2 = remaining.equals(remaining2.add(closer_product2));
		// System.out.println("\n\n");
		// System.out.println("product: "+ closer_product2);
		// System.out.println("Remaining: "+ remaining2);
		// System.out.println("product + remaining: " + closer_product2.add(remaining2));
		// System.out.println("Trailing Zeros: "+ trailingZeros2);
		// System.out.println("Zeros:"+ zeros2);
		// System.out.println("Equals:" + eq2 );

	}
}

