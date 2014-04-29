public class Matrix {

    private int size;
    private int[][] data;
    private static int numMultiplications;

    /*
     * Multiplikationszaehler loeschen
     */
    public static void clearMultCounter() {
        numMultiplications = 0;
    }
    
    public static void printMultCounter() {
        System.out.println("Multiplications: " + numMultiplications);
    }
    
    public int getSize() {
        return size;
    }
    
    public int[][] getData() {
        return data;
    }
    
    public Matrix(int size) {
        this.size = size;
        data = new int[size][size];
    }
    
    /*
     * Matrix mit Zufallszahlen zwischen min und max fuellen. 
     */
    public void populate(int min, int max) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                data[i][j] = (int)(Math.random() * (max-min) + min);
            }
        }
    }
    
    /*
     * Matrix mit identischen Werten (num) fuellen.
     */
    public void populate(int num) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                data[i][j] = num;
            }
        }
    }
    
    /* (Sub-)Matrix kopieren. 
     * x,y = Startpunkt
     * size = Breite der kopierenden Matrix  
     */
    public Matrix copy(int x, int y, int size) {
        Matrix m = new Matrix(size);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                m.getData()[i][j] = data[x+i][y+j];
            }
        }
        return m;
    }
    
    /*
     * Matrix in andere Matrix einfuegen.
     * x,y = Startpunkt zum Einfuegen
     */
    public void paste(Matrix m, int x, int y) {
        for (int i = 0; i < m.getSize(); i++) {
            for (int j = 0; j < m.getSize(); j++) {
                data[x+i][y+j] = m.getData()[i][j];
            }
        }
    }

    /*
     * Matrix addieren.
     */
    public Matrix plus(Matrix b) throws Exception {
        if (b.getSize() != size) {
            throw new Exception("Matrix add: Wrong matrix size!");
        }
        Matrix m = new Matrix(size);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                m.getData()[i][j] = data[i][j] + b.data[i][j];
            }
        }
        return m;
    }
    
    /* 
     * Matrix subtrahieren.
     */
    public Matrix minus(Matrix b) throws Exception {
        if (b.getSize() != size) {
            throw new Exception("Matrix sub: Wrong matrix size!");
        }
        Matrix m = new Matrix(size);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                m.getData()[i][j] = data[i][j] - b.data[i][j];
            }
        }
        return m;
    }
    
    /*
     * Matrix nach dem Standardverfahren multiplizieren. 
     */
    public Matrix mult(Matrix b) throws Exception {
        if (b.getSize() != size) {
            throw new Exception("Matrix mult: Wrong matrix size!");
        }
        Matrix m = new Matrix(size);

        // Hier Ihr Code...

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                for (int k = 0; k < size; k++) {
                    m.getData()[i][j] += data[i][k] * b.data[k][j];
                }
            }
        }
        return m;
    }

    /*
     * Matrix nach dem Strassen-Algorithmus multiplizieren
     */
    public Matrix strassenMult(Matrix b) throws Exception {
        if (b.getSize() != size) {
            throw new Exception("Matrix strassenMult: Wrong matrix size!");
        }

        Matrix m = new Matrix(size);
        m.populate(0);

        // Hier Ihr Code...

        if( b.getSize() == 2 )
        {
            int M1 = ( data[0][0] + data[1][1] )*( b.data[0][0] + b.data[1][1]);
            int M2 = ( data[1][0] + data[1][1] )*  b.data[0][0];
            int M3 =                data[0][0]  *( b.data[0][1] - b.data[1][1]);
            int M4 =                data[1][1]  *( b.data[1][0] - b.data[0][0]);
            int M5 = ( data[0][0] + data[0][1] )*  b.data[1][1];
            int M6 = ( data[1][0] - data[0][0] )*( b.data[0][0] + b.data[0][1]);
            int M7 = ( data[0][1] - data[1][1] )*( b.data[1][0] + b.data[1][1]);

            m.data[0][0] = M1 + M4 - M5 + M7;
            m.data[0][1] = M3 + M5;
            m.data[1][0] = M2 + M4;
            m.data[1][1] = M1 - M2 + M3 + M6;
        }
        else
        {
            Matrix a0 = new Matrix(size/2);
            Matrix a1 = new Matrix(size/2);
            Matrix a2 = new Matrix(size/2);
            Matrix a3 = new Matrix(size/2);
            a0 =   copy( 0,      0,      size/2 );
            a1 =   copy( 0,      size/2, size/2 );
            a2 =   copy( size/2, 0,      size/2 );
            a3 =   copy( size/2, size/2, size/2 );

            Matrix b0 = new Matrix(size/2);
            Matrix b1 = new Matrix(size/2);
            Matrix b2 = new Matrix(size/2);
            Matrix b3 = new Matrix(size/2);
            b0 = b.copy( 0,      0,      size/2 );
            b1 = b.copy( 0,      size/2, size/2 );
            b2 = b.copy( size/2, 0,      size/2 );
            b3 = b.copy( size/2, size/2, size/2 );

            Matrix M1 = new Matrix(size/2);
            Matrix M2 = new Matrix(size/2);
            Matrix M3 = new Matrix(size/2);
            Matrix M4 = new Matrix(size/2);
            Matrix M5 = new Matrix(size/2);
            Matrix M6 = new Matrix(size/2);
            Matrix M7 = new Matrix(size/2);
            M1 = ( a0.plus(a3)  ).strassenMult( b0.plus(b3) );
            M2 = ( a2.plus(a3)  ).strassenMult( b0 );
            M3 =               a0.strassenMult( b1.minus(b3) );
            M4 =               a3.strassenMult( b2.minus(b0) );
            M5 = ( a0.plus(a1)  ).strassenMult( b3);
            M6 = ( a2.minus(a0) ).strassenMult( b0.plus(b1) );
            M7 = ( a1.minus(a3) ).strassenMult( b2.plus(b3) );

            m.paste( ( M1.plus(M4).minus(M5).plus(M7) ), 0,      0      );
            m.paste( ( M3.plus(M5)                    ), 0,      size/2 );
            m.paste( ( M2.plus(M4)                    ), size/2, 0      );
            m.paste( ( M1.minus(M2).plus(M3).plus(M6) ), size/2, size/2 );
        }
        return m;
    }

    public String toString() {
        String s = "";
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                s += data[i][j] + "\t";
                if (j > 20) {
                    j = size;
                    s += "...";
                }
            }
            s += "\n";
            if (i > 20) {
                i = size;
                s += "...";
            }
        }
        //s += "Multiplications: " + numMultiplications;
        return s;
    }

    
    public static void main(String[] args) throws Exception {
        Matrix A = new Matrix(512);
        Matrix B = new Matrix(512);
        A.populate(1,10);
        B.populate(1,10);
        //System.out.println(A);
        //System.out.println(B);
        clearMultCounter();
        long startTime = System.currentTimeMillis();
        System.out.println(A.strassenMult(B));
        long stopTime = System.currentTimeMillis();
        System.out.println("Strassen: " + (stopTime-startTime)/1000 + "s");
        printMultCounter();
        clearMultCounter();
        startTime = System.currentTimeMillis();
        System.out.println(A.mult(B));
        stopTime = System.currentTimeMillis();
        System.out.println("Normal multiplication: " + (stopTime-startTime)/1000 + "s");
        printMultCounter();
    }
}
