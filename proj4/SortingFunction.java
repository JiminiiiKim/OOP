package 객지프_팀플4;

import java.util.ArrayList;
import java.util.Comparator;

public class SortingFunction {

	//dDay
	public static ArrayList<Assignment> assignmentDDaySorting(ArrayList<Assignment> assignments) {
		assignments.sort(Comparator.comparing(Assignment::getDDay));
		ArrayList<Assignment> result = new ArrayList<>();
		
		for(Assignment assignment : assignments) {
			result.add(assignment);
		}
		return result;
	}
		
	// priority
	public static ArrayList<Assignment> assignmentsPrioritySorting(ArrayList<Assignment> assignments) {
		assignments.sort(Comparator.comparing(Assignment::getPriority));
		ArrayList<Assignment> result = new ArrayList<>();

		for (Assignment assignment : assignments) {
			result.add(assignment);
		}
		return result;
	}

	
	// difficulty
	public static ArrayList<Assignment> assignmentsDifficultySorting(ArrayList<Assignment> assignments) {
		assignments.sort(Comparator.comparing(Assignment::getDifficulty));
		ArrayList<Assignment> result = new ArrayList<>();

		for (Assignment assignment : assignments) {
			result.add(assignment);
		}
		return result;
	}
	
	//dDay reverse
	public static ArrayList<Assignment> reverseAssignmentDDaySorting(ArrayList<Assignment> assignments) {
		assignments.sort(Comparator.comparing(Assignment::getDDay).reversed());
		ArrayList<Assignment> result = new ArrayList<>();
		
		for(Assignment assignment : assignments) {
			result.add(assignment);
		}
		return result;
	}

	// priority reverse
	public static ArrayList<Assignment> reverseAssignmentPrioritySorting(ArrayList<Assignment> assignments) {
		assignments.sort(Comparator.comparing(Assignment::getPriority).reversed());

		ArrayList<Assignment> result = new ArrayList<>();

		for (Assignment assignment : assignments) {
			result.add(assignment);
		}
		return result;
	}

	// difficulty reverse
	public static ArrayList<Assignment> reverseAssignmentDifficultySorting(ArrayList<Assignment> assignments) {
		assignments.sort(Comparator.comparing(Assignment::getDifficulty).reversed());

		ArrayList<Assignment> result = new ArrayList<>();

		for (Assignment assignment : assignments) {
			result.add(assignment);
		}
		return result;
	}

	/////////////////////////Exams//////////////////////////////////////
	
	//dDay
	public static ArrayList<Exam> examDDaySorting(ArrayList<Exam> exams) {
		exams.sort(Comparator.comparing(Exam::getDDay));
		ArrayList<Exam> result = new ArrayList<>();
		
		for(Exam exam : exams) {
			result.add(exam);
		}
		return result;
	}
	
	//priority
	public static ArrayList<Exam> examsPrioritySorting(ArrayList<Exam> exams) {
		exams.sort(Comparator.comparing(Exam::getPriority));
		ArrayList<Exam> result = new ArrayList<>();

		for (Exam exam : exams) {
			result.add(exam);
		}
		return result;
	}

	//difficulty
	public static ArrayList<Exam> examsDifficultySorting(ArrayList<Exam> exams) {
		exams.sort(Comparator.comparing(Exam::getDifficulty));
		ArrayList<Exam> result = new ArrayList<>();

		for (Exam exam : exams) {
			result.add(exam);
		}
		return result;
	}
	
	//dDay
	public static ArrayList<Exam> reverseExamDDaySorting(ArrayList<Exam> exams) {
		exams.sort(Comparator.comparing(Exam::getDDay).reversed());
		ArrayList<Exam> result = new ArrayList<>();
		
		for(Exam exam : exams) {
			result.add(exam);
		}
		return result;
	}
		
	//priority reverse
	public static ArrayList<Exam> reverseExamsPrioritySorting(ArrayList<Exam> exams) {
		exams.sort(Comparator.comparing(Exam::getPriority).reversed());

		ArrayList<Exam> result = new ArrayList<>();

		for (Exam exam : exams) {
			result.add(exam);
		}
		return result;
	}

	//difficulty reverse
	public static ArrayList<Exam> reverseExamsDifficultySorting(ArrayList<Exam> exams) {
		exams.sort(Comparator.comparing(Exam::getDifficulty).reversed());

		ArrayList<Exam> result = new ArrayList<>();

		for (Exam exam : exams) {
			result.add(exam);
		}
		return result;
	}
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	public static ArrayList<Assignment> searchAssignment(ArrayList<Assignment> assignments, String subjectName) {
		ArrayList<Assignment> result = new ArrayList<Assignment>();
		for(Assignment assignment: assignments) {
			if(assignment.getSubjectName().equals(subjectName)) {
				result.add(assignment);
			}
		}
		return result;
	}
	
	public static ArrayList<Exam> searchExam(ArrayList<Exam> exams, String subjectName) {
		ArrayList<Exam> result = new ArrayList<Exam>();
		for(Exam exam: exams) {
			if(exam.getSubjectName().equals(subjectName)) {
				result.add(exam);
			}
		}
		return result;
	}
}