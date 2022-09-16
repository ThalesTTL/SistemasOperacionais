public class Teste {

	public static void main(String[] args) {
		
		// Instaciamos os objetos básicos para a resolução do problema.
		Mesa mesa = new Mesa();
		
		Filosofo filosofo1 = new Filosofo("Filosofo 1");
		Filosofo filosofo2 = new Filosofo("Filosofo 2");
		Filosofo filosofo3 = new Filosofo("Filosofo 3");
		Filosofo filosofo4 = new Filosofo("Filosofo 4");
		Filosofo filosofo5 = new Filosofo("Filosofo 5");
		
		mesa.adicionar(filosofo1);
		mesa.adicionar(filosofo2);
		mesa.adicionar(filosofo3);
		mesa.adicionar(filosofo4);
		mesa.adicionar(filosofo5);
		
		/*
		 * Aqui, realizamos uma verificação de qual filósofo está ao lado direito e qual filósofo está ao lado esquerdo de cada filósofo.
		 * Em outras palavras, descobrimos quem está sentado ao lado de cada filósofo.
		 */
		filosofo1.setFilosofos(mesa.getFilosofoEsq(filosofo1), mesa.getFilosofoDir(filosofo1));
		filosofo2.setFilosofos(mesa.getFilosofoEsq(filosofo2), mesa.getFilosofoDir(filosofo2));
		filosofo3.setFilosofos(mesa.getFilosofoEsq(filosofo3), mesa.getFilosofoDir(filosofo3));
		filosofo4.setFilosofos(mesa.getFilosofoEsq(filosofo4), mesa.getFilosofoDir(filosofo4));
		filosofo5.setFilosofos(mesa.getFilosofoEsq(filosofo5), mesa.getFilosofoDir(filosofo5));
		
		// Instanciamos uma thread para cada filósofo, passando o objeto do tipo filósofo para o construtor da Thread.
		// Isso é necessário, porque quando a Thread for inicializada, ela chamará o método run() de cada filósofo.
		
		Thread thread1 = new Thread(filosofo1);
		Thread thread2 = new Thread(filosofo2);
		Thread thread3 = new Thread(filosofo3);
		Thread thread4 = new Thread(filosofo4);
		Thread thread5 = new Thread(filosofo5);
		
		// Iniciamos cada uma das Threads, que chamará o método run() de cada filósofo.
		thread1.start();
		thread2.start();
		thread3.start();
		thread4.start();
		thread5.start();
		
	}
	
	

}
