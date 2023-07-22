import { Component } from "react";
import Axios from "axios";
import Table from "react-bootstrap/Table";
import Button from "react-bootstrap/Button";

const Board = ({
    id,
    title,
    registerId,
    registerDate,
    props,
}: {
    id: number;
    title: string;
    registerId: string;
    registerDate: string;
    props: any;
}) => {
    return (
        <tr>
            <td>
                <input
                    type="checkbox"
                    value={id}
                    onChange={(e) => {
                        props.onCheckboxChange(e.currentTarget.checked, e.currentTarget.value);
                    }}
                ></input>
            </td>
            <td>{id}</td>
            <td>{title}</td>
            <td>{registerId}</td>
            <td>{registerDate}</td>
        </tr>
    );
};

interface IProps {
    isComplete: boolean;
    handleModify: any;
    renderComplete: any;
}

/**
 * BoardList class
 * @param {SS} e
 */
class BoardList extends Component<IProps> {
    /**
     * @param {SS} props
     */
    constructor(props: any) {
        super(props);
        this.state = {
            boardList: [],
            checkList: [],
        };
    }

    state = {
        boardList: [],
        checkList: [],
    };

    getList = () => {
        Axios.get("http://localhost:8000/list", {})
            .then((res) => {
                const { data } = res;
                this.setState({
                    boardList: data,
                });
                this.props.renderComplete();
            })
            .catch((e) => {
                console.error(e);
            });
    };

    /**
     * @param {boolean} checked
     * @param {any} id
     */
    onCheckboxChange = (checked: boolean, id: any) => {
        const list: Array<string> = this.state.checkList.filter((v) => {
            return v != id;
        });

        if (checked) {
            list.push(id);
        }

        this.setState({
            checkList: list,
        });
    };

    /**
     */
    componentDidMount() {
        this.getList();
    }

    /**
     */
    componentDidUpdate() {
        if (!this.props.isComplete) {
            this.getList();
        }
    }

    /**
     * @return {Component} Component
     */
    render() {
        const { boardList }: { boardList: any } = this.state;

        return (
            <div>
                <Table striped bordered hover>
                    <thead>
                        <tr>
                            <th>선택</th>
                            <th>번호</th>
                            <th>제목</th>
                            <th>작성자</th>
                            <th>작성일</th>
                        </tr>
                    </thead>
                    <tbody>
                        {boardList.map((v: any) => {
                            return (
                                    <Board
                                        id={v.idx}
                                        title={v.subject}
                                        registerId={v.name}
                                        registerDate={v.rdate}
										key={v.idx}
										props={this}
                                    />
                            );
                        })}
                    </tbody>
                </Table>
                <Button variant="info">글쓰기</Button>
                <Button
                    variant="secondary"
                    onClick={() => {
                        this.props.handleModify(this.state.checkList);
                    }}
                >
                    수정하기
                </Button>
                <Button variant="danger">삭제하기</Button>
            </div>
        );
    }
}

export default BoardList;