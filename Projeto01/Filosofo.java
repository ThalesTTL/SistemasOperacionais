public class Filosofo implements Runnable {

	private String nome;

	private boolean comendo;
	private boolean garfoDir;
	private boolean garfoEsq;

	private Filosofo filosofoEsq;
	private Filosofo filosofoDir;

	public Filosofo(String nome) {

		this.nome = nome;

		// Todos começam pensando
		this.comendo = false;

		// Todos começam sem garfos em mãos
		this.garfoEsq = false;
		this.garfoDir = false;

	}

	public void existir() {
		this.pensar();
		this.esperar();
		
		this.pegarGarfos();
		this.esperar();
		
		this.comer();
		this.esperar();
		
		this.devolverGarfos();
		this.esperar();
	}

	public void pensar() {
		this.comendo = false;
		System.out.println(this.nome + " esta pensando...");
		
	}

	private void pegarGarfos() {
		System.out.println(this.nome + " esta tentando pegar os garfos...");
		while (true) {
			if (!this.filosofoEsq.garfoDir && !this.filosofoDir.garfoEsq) {
				this.garfoEsq = true;
				this.garfoDir = true;
				break;
			}
			this.esperar();
		}

	}

	private void devolverGarfos() {
		this.garfoDir = false;
		this.garfoEsq = false;
	}

	private void comer() {
		System.out.println(this.nome + " esta comendo...");
		this.esperar();
		
		this.comendo = false;
	}

	private void esperar() {
		try {
			Thread.sleep(3000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}
	
	/****************************************************/

	public String getNome() {
		return this.nome;
	}

	public boolean estaComendo() {
		return comendo;
	}

	public Filosofo getFilosofoEsq() {
		return filosofoEsq;
	}

	public Filosofo getFilosofoDir() {
		return filosofoDir;
	}

	public void setFilosofos(Filosofo filosofoEsq, Filosofo filosofoDir) {
		this.filosofoEsq = filosofoEsq;
		this.filosofoDir = filosofoDir;
	}


	@Override
	public String toString() {
		return "Filosofo [nome=" + nome + "]";
	}

	@Override
	public void run() {
		while(true) {
			this.existir();
		}
	}

}
