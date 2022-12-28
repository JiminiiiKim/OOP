package 객지프_팀플4;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.TextField;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.Connection;
import java.sql.Statement;
import java.util.Calendar;
import java.util.GregorianCalendar;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.border.Border;

class calendardiary extends JPanel implements ActionListener
{
       String [] days = {"SUN","MON","TUE","WED","THU","FRI","SAT"};
       int year ,month,day,todays,memoday=0;

       Font f;
      
       Calendar today;
       Calendar cal;
  
       
       JButton[] calBtn = new JButton[49];
 
       JLabel time;
 
       JPanel panSouth;
       JPanel panNorth;
       JPanel panCenter;
                           
       JTextField txtMonth,txtYear;
       
       JTextArea txtWrite;
       BorderLayout bLayout= new BorderLayout();     
     
       Connection con = null;
       Statement stmt = null;
       
       
       
       public calendardiary(){
          
             today = Calendar.getInstance(); 
             cal = new GregorianCalendar();
             
             year = today.get(Calendar.YEAR);
             month = today.get(Calendar.MONTH)+1;
 
             panNorth = new JPanel();
                       
             
             panNorth.add(txtYear = new JTextField(year+"��"));
             panNorth.add(txtMonth = new JTextField( month+"��"));
           
             f=new Font("Sherif",Font.BOLD,18); 
             txtYear.setFont(f);
             txtMonth.setFont(f);
             
             txtYear.setEnabled(false); 
             txtMonth.setEnabled(false);
             
            
               
             add(panNorth,"North");

             
             panCenter = new JPanel(new GridLayout(7,7));//���ڳ�,���������� ��ġ������
             f=new Font("Sherif",Font.BOLD,12);
            
             gridInit();
             calSet();
             hideInit();
             add(panCenter,"Center");

            
             panSouth = new JPanel(); 
         
             add(panSouth,"South");        
         
             //setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
             setBounds(200,200,450,400);   
             setVisible(true); 
       }


       
       public void calSet(){
             cal.set(Calendar.YEAR,year);
             cal.set(Calendar.MONTH,(month-1));
             cal.set(Calendar.DATE,1);
             int dayOfWeek = cal.get(Calendar.DAY_OF_WEEK);

             int j=0;
             int hopping=0;
             calBtn[0].setForeground(new Color(255,0,0));
             calBtn[6].setForeground(new Color(0,0,255));

             for(int i=cal.getFirstDayOfWeek();i<dayOfWeek;i++){  j++;  }
            
             hopping=j;

             for(int kk=0;kk<hopping;kk++){
                    calBtn[kk+7].setText("");
             }
             for(int i=cal.getMinimum(Calendar.DAY_OF_MONTH);
                           i<=cal.getMaximum(Calendar.DAY_OF_MONTH);i++){
                 cal.set(Calendar.DATE,i);
                    if(cal.get(Calendar.MONTH) !=month-1){
                           break;
                    }
                   
                    todays=i;
                    
                    if(memoday==1){   
                           calBtn[i+6+hopping].setForeground(new Color(255,0,255));                         
                    }
                    else{
                           calBtn[i+6+hopping].setForeground(new Color(0,0,0));
                           if((i+hopping-1)%7==0){
                                 calBtn[i+6+hopping].setForeground(new Color(255,0,0));
                           }
                           if((i+hopping)%7==0){
                                 calBtn[i+6+hopping].setForeground(new Color(0,0,255));
                           }
                    }
                  
                    calBtn[i+6+hopping].setText((i)+"");
             }
 
       }
       
       public void actionPerformed(ActionEvent cook){   
           
           if(Integer.parseInt(cook.getActionCommand()) >= 1 && 
                  Integer.parseInt(cook.getActionCommand()) <=31){
                  day = Integer.parseInt(cook.getActionCommand());
                  
                  System.out.println(day);
                  Testing.date = 1200+day;
                  
                  List.CalendarPanel.add(Testing.printInfoPanel());
          		  List.CalendarPanel.add(Testing.addInfoPanel());
                  calSet();
           }      
     }

       public void hideInit(){
             for(int i = 0 ; i < calBtn.length;i++){
                    if((calBtn[i].getText()).equals(""))
                           calBtn[i].setEnabled(false);
             
             }
       }
 
       public void gridInit(){
         
         for(int i = 0 ; i < days.length;i++)
               panCenter.add(calBtn[i] = new JButton(days[i]));                   

           for(int i = days.length ; i < 49;i++){                
                    panCenter.add(calBtn[i] = new JButton(""));                   
                    calBtn[i].addActionListener(this);
             }              
       }
       
       public void panelInit(){
         GridLayout gridLayout1 = new GridLayout(7,7);
         panCenter.setLayout(gridLayout1);   
       }
       public void calInput(int gap){
                         
              if (gap==-1 || gap ==1)
              {
                 month+=(gap);
                 if (month<=0)
                 {
                      month = 12;
                      year  =year- 1;
                 }
                 else if (month>=13)
                 {
                      month = 1;
                      year =year+ 1;
                 }
              }
              else if(gap == 12){   year++;   }
              else if(gap == -12){   year--;   }
       }
}