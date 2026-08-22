package bint.utility;


import java.math.BigInteger;
import java.security.SecureRandom;



public class RSA {
    
    private static final SecureRandom RANDOM = new SecureRandom();

    static class InvalidPrimalityInputException extends IllegalArgumentException {public InvalidPrimalityInputException(String message) {super(message);}}

    public static void main(String[] args) {
        BigInteger p = generateRandomPrimeValues(2048, 10);
        BigInteger q = generateRandomPrimeValues(2048, 10);

       System.out.println(p.toByteArray());
       System.out.println(q.toByteArray());

    }

    static BigInteger generateRandomPrimeValues(int size, int iter) throws InvalidPrimalityInputException{ 
        while( iter-- > 0){
            BigInteger possiblePrime =  new BigInteger(size, RANDOM).abs();
             System.out.println(possiblePrime.toByteArray());
            if (possiblePrime.isProbablePrime(2)){
                return possiblePrime;
            }else{
                System.out.println("It isn't prime");
            }

        }
        throw new InvalidPrimalityInputException("The random wasn't generated");
    }
    
}

    
