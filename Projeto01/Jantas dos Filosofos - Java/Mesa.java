import java.util.LinkedList;

public class Mesa {
	
	// Criamos uma LinkedList do tipo Filosofo, para armazenar cada um dos filósofos instanciados na função principal.
	LinkedList<Filosofo> filosofos = new LinkedList<Filosofo>();
	
	public Mesa() {}
	
	// Adiciona um filósofo a lista de filósofos.
	public void adicionar(Filosofo filosofo) {
		this.filosofos.add(filosofo);
	}
	
	// Método criado para descobrir qual filósofo está a esquerda do filósofo passado como parâmetro.
	public Filosofo getFilosofoEsq(Filosofo filosofo) {

		Filosofo filosofoEsq;
		
		// Pegamos o index do filósofo
		int indexFilosofo = filosofos.indexOf(filosofo);
		// Se o filósofo estiver na primeira posição da LinkedList...
		if(indexFilosofo == 0) {
			// O filósofo a esquerda dele, vai ser o último da lista.
			filosofoEsq = filosofos.getLast();
		} else {
			// Caso contrário, o filósofo a esquerda dele, será aquele que está no index - 1.
			filosofoEsq = filosofos.get(indexFilosofo - 1);
		}
		
		return filosofoEsq;
	}
	// Método criado para descobrir qual filósofo está a direita do filósofo passado como parâmetro.
	public Filosofo getFilosofoDir(Filosofo filosofo) {
		
		Filosofo filosofoDir;
		// Pegamos o index do filósofo
		int indexFilosofo = filosofos.indexOf(filosofo);
		// Se o index do filósofo foi igual ao index do último elemento da LinkedList...
		// Ou seja, se o meu filósofo passado como parâmetro for o último da lista...
		if(indexFilosofo == filosofos.indexOf(filosofos.getLast())) {
			// O filósofo a direita dele será o primeiro da lista.
			filosofoDir = filosofos.getFirst();
		} else {
			// Caso contrário, o filósofo a direita dele será aquele que está no index + 1.
			filosofoDir = filosofos.get(indexFilosofo + 1); 
		}
		
		return filosofoDir;
	}
	
	// Método criado para retornar os elementos dentro da lista de filósofos.
	public LinkedList<Filosofo> getList(){
		return this.filosofos;
	}
	
	
	
	
}
