import java.util.LinkedList;

public class Mesa {
	
	LinkedList<Filosofo> filosofos = new LinkedList<Filosofo>();
	
	public Mesa() {}
	
	public void adicionar(Filosofo filosofo) {
		this.filosofos.add(filosofo);
	}

	public Filosofo getFilosofoEsq(Filosofo filosofo) {

		Filosofo filosofoEsq;
		
		int indexFilosofo = filosofos.indexOf(filosofo);
		if(indexFilosofo == 0) {
			filosofoEsq = filosofos.getLast();
		} else {
			filosofoEsq = filosofos.get(indexFilosofo - 1);
		}
		
		return filosofoEsq;
	}
	
	public Filosofo getFilosofoDir(Filosofo filosofo) {
		
		Filosofo filosofoDir;
		
		int indexFilosofo = filosofos.indexOf(filosofo);
		if(indexFilosofo == filosofos.indexOf(filosofos.getLast())) {
			filosofoDir = filosofos.getFirst();
		} else {
			filosofoDir = filosofos.get(indexFilosofo + 1); 
		}
		
		return filosofoDir;
	}
	
	public LinkedList<Filosofo> getList(){
		return this.filosofos;
	}
	
	
	
	
}
