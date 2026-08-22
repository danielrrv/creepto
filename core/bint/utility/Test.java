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
		// BigInteger A = new BigInteger("2989540626429799377152730000884577418714682383919291882126");
		// BigInteger B = new BigInteger("5774187146823839192918821268");

		// System.out.println("Result: " + A.divide(B));

		// KeyPairGenerator generator = KeyPairGenerator.getInstance("RSA");
		// generator.initialize(2048);
		// KeyPair pair = generator.generateKeyPair();

		// PrivateKey privateKey = pair.getPrivate();
		// PublicKey publicKey = pair.getPublic();

		// System.out.println(privateKey.getEncoded());

		BigInteger q  = generateRandomBigNumber(2048 / 2);
		System.out.println(q);

	}

	public static BigInteger generateRandomBigNumber(int size) {
		return new BigInteger(size, new Random()).abs();
	}
}
