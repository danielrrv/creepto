package bint.utility;
import java.math.BigInteger;
import java.util.Random;
// import java.security.KeyPairGenerator;
// import java.security.KeyPair;
// import java.security.PrivateKey;
// import java.security.PublicKey;
import java.security.*;

class Test {
	public static void main(String[] args) throws Exception {
		System.err.println("hello");

		BigInteger A = new BigInteger("3324298954062642979937715273000088457741871468238391929188212688");
		BigInteger B = new BigInteger("157624825433230490762246168127797657567916321816555529634539929");
		
		BigInteger gcd = A.gcd(B); // Returns 9

        // Calculate LCM: (A * B) / GCD
        // Dividing first prevents the intermediate product from bloating unnecessarily
        BigInteger lcm = A.divide(gcd).multiply(B);

        System.out.println("LCM: " + lcm);
		

		// System.out.println("Result: " + A.divide(B));

		// KeyPairGenerator generator = KeyPairGenerator.getInstance("RSA");
		// generator.initialize(2048);
		// KeyPair pair = generator.generateKeyPair();

		// PrivateKey privateKey = pair.getPrivate();
		// PublicKey publicKey = pair.getPublic();

		// System.out.println(privateKey.getEncoded());

		// BigInteger q  = generateRandomBigNumber(2048 / 2);
		// System.out.println(q);

	}

	public static BigInteger generateRandomBigNumber(int size) {
		return new BigInteger(size, new Random()).abs();
	}
}
