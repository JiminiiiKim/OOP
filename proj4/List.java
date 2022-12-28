package 객지프_팀플4;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.ScrollPaneConstants;
import javax.swing.table.DefaultTableModel;

class SortActionHandler implements ActionListener { 
	private JButton button;
	// private JTextArea asmt_txtarea, exm_txtarea;
	private DefaultTableModel asmt_model, exm_model;
	private JTable asmt_table, exm_table;
	static boolean dday_ascending = false, priority_ascending = false, difficulty_ascending = false; 
																																																																													

	public SortActionHandler(JButton button, DefaultTableModel asmt_model, JTable asmt_table,
			DefaultTableModel exm_model, JTable exm_table) {

		this.button = button;
		this.asmt_model = asmt_model;
		this.asmt_table = asmt_table;
		this.exm_model = exm_model;
		this.exm_table = exm_table;
	}

	@Override
	public void actionPerformed(ActionEvent e) {

		// get all data
		ArrayList<Assignment> assignments = new ArrayList<Assignment>();
		assignments = SaveInfo.asList();
		ArrayList<Exam> exams = new ArrayList<Exam>();
		exams = SaveInfo.exList();

		if (button.getText().equals("D-DAY")) {
			// button.setText("pressed");
				
			if (dday_ascending == false)
				dday_ascending = true;
			else 
				dday_ascending = false;
			//System.out.println(dday_ascending);
			if (dday_ascending == false) {
				DefaultTableModel asmt_model = (DefaultTableModel) asmt_table.getModel();
				asmt_model.setNumRows(0);

				ArrayList<Assignment> resultAssignment = SortingFunction.assignmentDDaySorting(assignments);
				
				for (int i = 0; i < resultAssignment.size(); i++) {
					String inputStr[] = new String[6];
					inputStr[0] = resultAssignment.get(i).getSubjectName();
					inputStr[1] = resultAssignment.get(i).getTitle();
					inputStr[2] = Integer.toString(resultAssignment.get(i).getDDay());
					inputStr[3] = Integer.toString(resultAssignment.get(i).getPriority());
					inputStr[4] = Integer.toString(resultAssignment.get(i).getDifficulty());
					inputStr[5] = resultAssignment.get(i).getMemo();
					asmt_model.addRow(inputStr);
				}

				DefaultTableModel exm_model = (DefaultTableModel) exm_table.getModel();
				exm_model.setNumRows(0);

				ArrayList<Exam> resultExam = SortingFunction.examDDaySorting(exams);

				for (int i = 0; i < resultExam.size(); i++) {
					String inputStr[] = new String[6];
					inputStr[0] = resultExam.get(i).getSubjectName();
					inputStr[1] = resultExam.get(i).getTestRange();
					inputStr[2] = Integer.toString(resultExam.get(i).getDDay());
					inputStr[3] = Integer.toString(resultExam.get(i).getPriority());
					inputStr[4] = Integer.toString(resultExam.get(i).getDifficulty());
					inputStr[5] = resultExam.get(i).getMemo();
					exm_model.addRow(inputStr);
				}
			}
			else if (dday_ascending == true) {
				// reversed
				DefaultTableModel asmt_model = (DefaultTableModel) asmt_table.getModel();
				asmt_model.setNumRows(0);

				ArrayList<Assignment> resultAssignment = SortingFunction.reverseAssignmentDDaySorting(assignments);

				for (int i = 0; i < resultAssignment.size(); i++) {
					String inputStr[] = new String[6];
					inputStr[0] = resultAssignment.get(i).getSubjectName();
					inputStr[1] = resultAssignment.get(i).getTitle();
					inputStr[2] = Integer.toString(resultAssignment.get(i).getDDay());
					inputStr[3] = Integer.toString(resultAssignment.get(i).getPriority());
					inputStr[4] = Integer.toString(resultAssignment.get(i).getDifficulty());
					inputStr[5] = resultAssignment.get(i).getMemo();
					asmt_model.addRow(inputStr);
				}
				DefaultTableModel exm_model = (DefaultTableModel) exm_table.getModel();
				exm_model.setNumRows(0);

				ArrayList<Exam> resultExam = SortingFunction.reverseExamDDaySorting(exams);

				for (int i = 0; i < resultExam.size(); i++) {
					String inputStr[] = new String[6];
					inputStr[0] = resultExam.get(i).getSubjectName();
					inputStr[1] = resultExam.get(i).getTestRange();
					inputStr[2] = Integer.toString(resultExam.get(i).getDDay());
					inputStr[3] = Integer.toString(resultExam.get(i).getPriority());
					inputStr[4] = Integer.toString(resultExam.get(i).getDifficulty());
					inputStr[5] = resultExam.get(i).getMemo();
					exm_model.addRow(inputStr);
				}
			}
		}

		else if (button.getText().equals("PRIORITY")) {
			// button.setText("pressed");
			
			if (priority_ascending == false)
				priority_ascending = true;
			else
				priority_ascending = false;
			if (priority_ascending == false) {
				DefaultTableModel asmt_model = (DefaultTableModel) asmt_table.getModel();
				asmt_model.setNumRows(0);

				ArrayList<Assignment> resultAssignment = SortingFunction.assignmentsPrioritySorting(assignments);

				for (int i = 0; i < resultAssignment.size(); i++) {
					String inputStr[] = new String[6];
					inputStr[0] = resultAssignment.get(i).getSubjectName();
					inputStr[1] = resultAssignment.get(i).getTitle();
					inputStr[2] = Integer.toString(resultAssignment.get(i).getDDay());
					inputStr[3] = Integer.toString(resultAssignment.get(i).getPriority());
					inputStr[4] = Integer.toString(resultAssignment.get(i).getDifficulty());
					inputStr[5] = resultAssignment.get(i).getMemo();
					asmt_model.addRow(inputStr);
				}

				DefaultTableModel exm_model = (DefaultTableModel) exm_table.getModel();
				exm_model.setNumRows(0);

				ArrayList<Exam> resultExam = SortingFunction.examsPrioritySorting(exams);

				for (int i = 0; i < resultExam.size(); i++) {
					String inputStr[] = new String[6];
					inputStr[0] = resultExam.get(i).getSubjectName();
					inputStr[1] = resultExam.get(i).getTestRange();
					inputStr[2] = Integer.toString(resultExam.get(i).getDDay());
					inputStr[3] = Integer.toString(resultExam.get(i).getPriority());
					inputStr[4] = Integer.toString(resultExam.get(i).getDifficulty());
					inputStr[5] = resultExam.get(i).getMemo();
					exm_model.addRow(inputStr);
				}
				
			} else if (priority_ascending == true) {
				// reversed
				DefaultTableModel asmt_model = (DefaultTableModel) asmt_table.getModel();
				asmt_model.setNumRows(0);

				ArrayList<Assignment> resultAssignment = SortingFunction.reverseAssignmentPrioritySorting(assignments);

				for (int i = 0; i < resultAssignment.size(); i++) {
					String inputStr[] = new String[6];
					inputStr[0] = resultAssignment.get(i).getSubjectName();
					inputStr[1] = resultAssignment.get(i).getTitle();
					inputStr[2] = Integer.toString(resultAssignment.get(i).getDDay());
					inputStr[3] = Integer.toString(resultAssignment.get(i).getPriority());
					inputStr[4] = Integer.toString(resultAssignment.get(i).getDifficulty());
					inputStr[5] = resultAssignment.get(i).getMemo();
					asmt_model.addRow(inputStr);
				}

				DefaultTableModel exm_model = (DefaultTableModel) exm_table.getModel();
				exm_model.setNumRows(0);

				ArrayList<Exam> resultExam = SortingFunction.reverseExamsPrioritySorting(exams);

				for (int i = 0; i < resultExam.size(); i++) {
					String inputStr[] = new String[6];
					inputStr[0] = resultExam.get(i).getSubjectName();
					inputStr[1] = resultExam.get(i).getTestRange();
					inputStr[2] = Integer.toString(resultExam.get(i).getDDay());
					inputStr[3] = Integer.toString(resultExam.get(i).getPriority());
					inputStr[4] = Integer.toString(resultExam.get(i).getDifficulty());
					inputStr[5] = resultExam.get(i).getMemo();
					exm_model.addRow(inputStr);
				}
			}
		}

		else if (button.getText().equals("DIFFICULTY")) {
			// button.setText("pressed");

			if (priority_ascending == false)
				priority_ascending = true;
			else
				priority_ascending = false;
			if (difficulty_ascending == false) {
				DefaultTableModel asmt_model = (DefaultTableModel) asmt_table.getModel();
				asmt_model.setNumRows(0);

				ArrayList<Assignment> resultAssignment = SortingFunction.assignmentsDifficultySorting(assignments);

				for (int i = 0; i < resultAssignment.size(); i++) {
					String inputStr[] = new String[6];
					inputStr[0] = resultAssignment.get(i).getSubjectName();
					inputStr[1] = resultAssignment.get(i).getTitle();
					inputStr[2] = Integer.toString(resultAssignment.get(i).getDDay());
					inputStr[3] = Integer.toString(resultAssignment.get(i).getPriority());
					inputStr[4] = Integer.toString(resultAssignment.get(i).getDifficulty());
					inputStr[5] = resultAssignment.get(i).getMemo();
					asmt_model.addRow(inputStr);
				}

				DefaultTableModel exm_model = (DefaultTableModel) exm_table.getModel();
				exm_model.setNumRows(0);

				ArrayList<Exam> resultExam = SortingFunction.examsDifficultySorting(exams);

				for (int i = 0; i < resultExam.size(); i++) {
					String inputStr[] = new String[6];
					inputStr[0] = resultExam.get(i).getSubjectName();
					inputStr[1] = resultExam.get(i).getTestRange();
					inputStr[2] = Integer.toString(resultExam.get(i).getDDay());
					inputStr[3] = Integer.toString(resultExam.get(i).getPriority());
					inputStr[4] = Integer.toString(resultExam.get(i).getDifficulty());
					inputStr[5] = resultExam.get(i).getMemo();
					exm_model.addRow(inputStr);
				}

				if (difficulty_ascending == false)
					difficulty_ascending = true;
				else
					difficulty_ascending = false;
			}

			else if (difficulty_ascending == true) {
				DefaultTableModel asmt_model = (DefaultTableModel) asmt_table.getModel();
				asmt_model.setNumRows(0);

				ArrayList<Assignment> resultAssignment = SortingFunction
						.reverseAssignmentDifficultySorting(assignments);

				for (int i = 0; i < resultAssignment.size(); i++) {
					String inputStr[] = new String[6];
					inputStr[0] = resultAssignment.get(i).getSubjectName();
					inputStr[1] = resultAssignment.get(i).getTitle();
					inputStr[2] = Integer.toString(resultAssignment.get(i).getDDay());
					inputStr[3] = Integer.toString(resultAssignment.get(i).getPriority());
					inputStr[4] = Integer.toString(resultAssignment.get(i).getDifficulty());
					inputStr[5] = resultAssignment.get(i).getMemo();
					asmt_model.addRow(inputStr);
				}

				DefaultTableModel exm_model = (DefaultTableModel) exm_table.getModel();
				exm_model.setNumRows(0);

				ArrayList<Exam> resultExam = SortingFunction.examsDifficultySorting(exams);

				for (int i = 0; i < resultExam.size(); i++) {
					String inputStr[] = new String[6];
					inputStr[0] = resultExam.get(i).getSubjectName();
					inputStr[1] = resultExam.get(i).getTestRange();
					inputStr[2] = Integer.toString(resultExam.get(i).getDDay());
					inputStr[3] = Integer.toString(resultExam.get(i).getPriority());
					inputStr[4] = Integer.toString(resultExam.get(i).getDifficulty());
					inputStr[5] = resultExam.get(i).getMemo();
					exm_model.addRow(inputStr);
				}

				if (difficulty_ascending == false)
					difficulty_ascending = true;
				else
					difficulty_ascending = false;
			}
		}

	}
}

/*when search*/
class SearchActionHandler implements ActionListener {
	private JTextField text_field;
	// private JTextArea asmt_txtarea, exm_txtarea;
	private DefaultTableModel asmt_model, exm_model;
	private JTable asmt_table, exm_table;


	public SearchActionHandler(JTextField text_field, DefaultTableModel asmt_model, JTable asmt_table,
			DefaultTableModel exm_model, JTable exm_table) {
		this.text_field = text_field;
		this.asmt_model = asmt_model;
		this.asmt_table = asmt_table;
		this.exm_model = exm_model;
		this.exm_table = exm_table;
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		SortActionHandler.dday_ascending = false;
		SortActionHandler.priority_ascending = false;
		SortActionHandler.difficulty_ascending = false;

		DefaultTableModel asmt_model = (DefaultTableModel) asmt_table.getModel();
		asmt_model.setNumRows(0);
		DefaultTableModel exm_model = (DefaultTableModel) exm_table.getModel();
		exm_model.setNumRows(0);

		String subject = text_field.getText();

		// get all assignments, exams
		ArrayList<Assignment> assignments = new ArrayList<Assignment>();
		assignments = SaveInfo.asList();
		ArrayList<Exam> exams = new ArrayList<Exam>();
		exams = SaveInfo.exList();

		ArrayList<Assignment> resultAssignment = SortingFunction.searchAssignment(assignments, subject);
		ArrayList<Exam> resultExam = SortingFunction.searchExam(exams, subject);

		for (int i = 0; i < resultAssignment.size(); i++) {
			String inputStr[] = new String[6];
			inputStr[0] = resultAssignment.get(i).getSubjectName();
			inputStr[1] = resultAssignment.get(i).getTitle();
			inputStr[2] = Integer.toString(resultAssignment.get(i).getDDay());
			inputStr[3] = Integer.toString(resultAssignment.get(i).getPriority());
			inputStr[4] = Integer.toString(resultAssignment.get(i).getDifficulty());
			inputStr[5] = resultAssignment.get(i).getMemo();
			asmt_model.addRow(inputStr);
		}

		for (int i = 0; i < resultExam.size(); i++) {
			String inputStr[] = new String[6];
			inputStr[0] = resultExam.get(i).getSubjectName();
			inputStr[1] = resultExam.get(i).getTestRange();
			inputStr[2] = Integer.toString(resultExam.get(i).getDDay());
			inputStr[3] = Integer.toString(resultExam.get(i).getPriority());
			inputStr[4] = Integer.toString(resultExam.get(i).getDifficulty());
			inputStr[5] = resultExam.get(i).getMemo();
			exm_model.addRow(inputStr);
		}

	}
}

public class List extends JFrame {
	public static JPanel CalendarPanel=new JPanel();
	public List(ArrayList<Assignment> as, ArrayList<Exam> ex) {
		JTabbedPane tab = new JTabbedPane(JTabbedPane.TOP);
		JFrame f = new JFrame("WHAT SHOULD WE DO FIRST?");
		f.getContentPane().add(tab, "Center");
		f.setSize(500, 400);

		/* Calendar */
		CalendarPanel = new JPanel();
		CalendarPanel.setBackground(new Color(207, 227, 250));
		tab.add("Calendar", CalendarPanel); 
		CalendarPanel.add(Testing.calendarPanel());
		CalendarPanel.add(Testing.printInfoPanel());
		CalendarPanel.add(Testing.addInfoPanel());
		//CalendarPanel.add(Testing.printInfoPanel());
		//CalendarPanel.add(Testing.addInfoPanel());
		
		/* List */
		JPanel ListPanel = new JPanel();
		ListPanel.setBackground(Color.WHITE);
		ListPanel.setOpaque(false);

		
		/* Search */
		JPanel inputPanel = new JPanel();
		inputPanel.setBackground(Color.WHITE);
		JButton search_button = new JButton("SEARCH");
		search_button.setBackground(new Color(207, 227, 250));
		search_button.setLocation(130, 50);
		JTextField text_field = new JTextField(20);
		inputPanel.add(new JLabel("Enter subject name."));
		inputPanel.add(text_field);
		inputPanel.add(search_button);
		ListPanel.setLocation(0, 30);
		ListPanel.add(inputPanel);

		
		/* sort button */
		JPanel sortPanel = new JPanel();
		sortPanel.setBackground(Color.WHITE);

		JButton dday_button = new JButton("D-DAY");
		dday_button.setBackground(new Color(207, 227, 250));
		// priority_button.setLocation(10, 30);
		sortPanel.add(dday_button);
		// dday_button.addActionListener(new SortActionHandler(dday_button,asmt_textArea, exm_textArea));

		JButton priority_button = new JButton("PRIORITY");
		priority_button.setBackground(new Color(207, 227, 250));
		// priority_button.setLocation(10, 30);
		sortPanel.add(priority_button);
		// priority_button.addActionListener(new SortActionHandler(priority_button,asmt_textArea, exm_textArea));

		JButton difficulty_button = new JButton("DIFFICULTY");
		difficulty_button.setBackground(new Color(207, 227, 250));
		// difficulty_button.setLocation(20, 30);
		sortPanel.add(difficulty_button);
		// difficulty_button.addActionListener(new SortActionHandler(difficulty_button, asmt_textArea, exm_textArea));

		sortPanel.setLocation(10, 30);
		ListPanel.add(sortPanel);

		
		/* assignment area */
		JPanel AssignmentPanel = new JPanel();
		AssignmentPanel.setBackground(Color.WHITE);
		AssignmentPanel.setSize(800, 300);
		AssignmentPanel.add(new JLabel("ASSIGNMENTS"));
		// JTextArea asmt_textArea = new JTextArea(21, 110);
		// asmt_textArea.setEditable(false);

		String asmt_header[] = { "SUBJECT NAME", "TITLE", "D-DAY", "PRIORITY", "DIFFICULTY", "MEMO" };
		String asmt_contents[][] = {}; 

		DefaultTableModel asmt_model = new DefaultTableModel(asmt_contents, asmt_header);
		JTable asmt_table = new JTable(asmt_model);
		JScrollPane asmt_scroll = new JScrollPane(asmt_table);
		asmt_scroll.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);
		AssignmentPanel.add(asmt_scroll);
		asmt_scroll.setPreferredSize(new Dimension(1100, 300));
		ListPanel.add(AssignmentPanel, BorderLayout.CENTER);

		ArrayList<Assignment> assignments = new ArrayList<Assignment>();
		assignments = as;

		for (int i = 0; i < assignments.size(); i++) {
			String inputStr[] = new String[6];
			inputStr[0] = assignments.get(i).getSubjectName();
			inputStr[1] = assignments.get(i).getTitle();
			inputStr[2] = Integer.toString(assignments.get(i).getDDay());
			inputStr[3] = Integer.toString(assignments.get(i).getPriority());
			inputStr[4] = Integer.toString(assignments.get(i).getDifficulty());
			inputStr[5] = assignments.get(i).getMemo();
			asmt_model.addRow(inputStr);
		}
		

		/* exam area */
		JPanel ExamPanel = new JPanel();
		ExamPanel.setBackground(Color.WHITE);
		ExamPanel.setSize(500, 300);
		ExamPanel.add(new JLabel("                EXAM"));

		String exm_header[] = { "SUBJECT NAME", "TEST RANGE", "D-DAY", "PRIORITY", "DIFFICULTY", "MEMO" };
		String exm_contents[][] = {};

		DefaultTableModel exm_model = new DefaultTableModel(exm_contents, exm_header);
		JTable exm_table = new JTable(exm_model);
		JScrollPane exm_scroll = new JScrollPane(exm_table);
		exm_scroll.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);
		ExamPanel.add(exm_scroll);
		exm_scroll.setPreferredSize(new Dimension(1100, 300));
		ListPanel.add(ExamPanel, BorderLayout.SOUTH);

		// get all assignments, exams
		ArrayList<Exam> exams = new ArrayList<Exam>();
		exams = ex;

		for (int i = 0; i < exams.size(); i++) {
			String inputStr[] = new String[6];
			inputStr[0] = exams.get(i).getSubjectName();
			inputStr[1] = exams.get(i).getTestRange();
			inputStr[2] = Integer.toString(exams.get(i).getDDay());
			inputStr[3] = Integer.toString(exams.get(i).getPriority());
			inputStr[4] = Integer.toString(exams.get(i).getDifficulty());
			inputStr[5] = exams.get(i).getMemo();
			exm_model.addRow(inputStr);
		}

		search_button.addActionListener(new SearchActionHandler(text_field, asmt_model, asmt_table, exm_model, exm_table));
		text_field.addActionListener(new SearchActionHandler(text_field, asmt_model, asmt_table, exm_model, exm_table)); // enter키 눌러서도 검색할 수 있도록
																																																													// �����ϵ���
		dday_button.addActionListener(new SortActionHandler(dday_button, asmt_model, asmt_table, exm_model, exm_table));
		priority_button.addActionListener(
				new SortActionHandler(priority_button, asmt_model, asmt_table, exm_model, exm_table));
		difficulty_button.addActionListener(
				new SortActionHandler(difficulty_button, asmt_model, asmt_table, exm_model, exm_table));

		tab.add("List", ListPanel); // List tab 추가

		f.getContentPane().add(tab, "Center");
		f.setDefaultCloseOperation(f.EXIT_ON_CLOSE);
		f.pack();
		f.setVisible(true);
	}

	public static void main(String[] args) {
		//new List();
	}

}


