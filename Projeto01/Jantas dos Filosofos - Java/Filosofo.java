// A nossa classe Filosofo implementa a interface Runnable, pois é ela que permite o funcionamento com Threads e nos fornece o método run(), que é acionado pelo método start() na função principal.
public class Filosofo implements Runnable {
	
	private String nome;
	
	// Variável para conferir se o filósofo está comendo ou pensando
	// true = comendo
	// false = pensando
	private boolean comendo;
	// Indica se o filósofo está com o garfo à direita dele nas mãos.
	// true = sim
	// false = não
	private boolean garfoDir;
	// Indica se o filósofo está com o garfo à esquerda dele nas mãos.
	// true = sim
	// false = não
	private boolean garfoEsq;

	// Uma referência para o filósofo à esquerda.
	private Filosofo filosofoEsq;
	// Uma referência para o filósofo à direita.
	private Filosofo filosofoDir;

	// Um construtor para a classe Filosofo, onde é obrigatório, no momento de sua criação, informar um nome para o filósofo.
	public Filosofo(String nome) {
		
		// O nome passado, será o nome do filósofo
		this.nome = nome;

		// Todos os filósofos instanciados começam sua existência pensando.
		this.comendo = false;

		// Todos os filósofos instanciados começam sem estar com os garfos em mãos
		this.garfoEsq = false;
		this.garfoDir = false;

	}
	
	// Rotina padrão de todo filósofo
	public void existir() {
		this.pensar();
		this.pegarGarfos();
		this.comer();
		this.devolverGarfos();
	}
	
	// Esse método faz o filósofo pensar.
	public void pensar() {
		// O filósofo está pensando, logo, ele não está comendo.
		this.comendo = false;
		System.out.println(this.nome + " esta pensando...");
		this.esperar();
	}
	
	// Esse método faz o filósofo pegar os garfos da direita e da esquerda.
	private void pegarGarfos() {
		// Criamos um loop para que o filósofo continue tentando pegar os dois garfos até conseguir ambos.
		while (true) {
			System.out.println(this.nome + " esta tentando pegar os garfos...");
			/*
			 * Se o filósofo a esquerda não estiver usando o garfo a direita dele
			 * &&
			 * Se o filósofo a direita não estiver usando o garfo a esquerda dele...
			 */
			if (!this.filosofoEsq.garfoDir && !this.filosofoDir.garfoEsq) {
				// O filósofo atual pega ambos os garfos.
				this.garfoEsq = true;
				this.garfoDir = true;
				break;
			}
			this.esperar();
		}
	}
	
	// Método que faz o filósofo comer.
	private void comer() {
		System.out.println(this.nome + " esta comendo...");
		this.esperar();
		// Após comer, definimos o valor da variável 'comendo' como false, para representar que o filósofo parou de comer.
		this.comendo = false;
	}
	
	// Método que faz o filósofo devolver os garfos.
	private void devolverGarfos() {
		// O filósofo devolve os dois garfos a mesa.
		this.garfoDir = false;
		this.garfoEsq = false;
		this.esperar();
	}
	
	// Criamos esse método 'esperar()', para que seja possível ler com mais tranquilidade o que acontece na tela.
	// Caso queira analisar mais lentamente o funcionamento do nosso código, basta inserir um valor maior.
	// Ex: 5000ms = 5s
	private void esperar() {
		// Aqui, utilizamos o try-catch para tratar e exceção InterruptedException lançada pelo método sleep().
		try {
			Thread.sleep(3000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}
	
	// Retorna o nome do filósofo
	public String getNome() {
		return this.nome;
	}
	
	// Verifica se o filósofo está comendo
	public boolean estaComendo() {
		return comendo;
	}
	
	// Retorna o filósofo a esquerda do filósofo atual
	public Filosofo getFilosofoEsq() {
		return filosofoEsq;
	}
	
	// Retorna o filósofo a direita do filósofo atual
	public Filosofo getFilosofoDir() {
		return filosofoDir;
	}
	
	// Define os filósofos a esquerda e a direita do filósofo atual
	public void setFilosofos(Filosofo filosofoEsq, Filosofo filosofoDir) {
		this.filosofoEsq = filosofoEsq;
		this.filosofoDir = filosofoDir;
	}

	// Método que formata a saída do objeto.
	// Ex: System.out.println(filosofo) -> saída: Filosofo [nome= filosofo x]
	@Override
	public String toString() {
		return "Filosofo [nome=" + nome + "]";
	}
	
	// Esse é o método run() sobrescrito da interface Runnable
	// Toda vez que uma thread é inicializada, esse método é executado.
	@Override
	public void run() {
		// Inserimos um loop infinito, para que a rotina do filósofo seja repetida infinitamente.
		while (true) {
			// Executa o método existir() do objeto atual.
			this.existir();
		}

	}

}
