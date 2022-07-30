package record;

public class Record 
{
    private int ID;

    private String field_1 = null;
    private int field_2;
    private float field_3;

    public Record(int ID, String field_1, int field_2, float field_3) 
    {
        this.ID = ID;

        this.field_1 = field_1;
        this.field_2 = field_2;
        this.field_3 = field_3;
    }

    public int getID(){ return this.ID; }
    
    public String getField_1(){ return this.field_1; }
    public int getField_2(){ return this.field_2; }
    public float getField_3(){ return this.field_3; }
}
